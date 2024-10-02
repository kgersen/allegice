//Copyright (C) Microsoft Corporation.  All rights reserved.
// kgersen = heavily modified to "flatten" and "single line"ing the output
using IGCLib;
using System.Collections;
using System.Reflection;

namespace igcexport;

public class ObjectDumper {

    public static void Write(string prefix, object element)
    {
        Write(Console.Out, prefix, element);
    }

    public static void Write(TextWriter w, string prefix, object element)
    {
        ObjectDumper dumper = new();
        dumper.WriteObject(w,prefix, element);
    }

    int pos;

    private ObjectDumper()
    {
    }

    private void Write(TextWriter w, string? s)
    {
        if (s != null) {
            w.Write(s);
            pos += s.Length;
        }
    }

    private void WriteLine(TextWriter w)
    {
        w.WriteLine();
        pos = 0;
    }

    private void WriteTab(TextWriter w)
    {
        Write(w,"  ");
        while (pos % 8 != 0) Write(w, " ");
    }

    private void WriteObject(TextWriter w,string prefix, object element)
    {
        if (element == null || element is ValueType || element is string || element is TechTreeBitMask) {
            Write(w,prefix);
            WriteValue(w,element);
            WriteLine(w);
        }
        else
        {
            if (element is IEnumerable enumerableElement)
            {
                foreach (object item in enumerableElement)
                {
                    if (item is IEnumerable && item is not string)
                    {
                        Write(w,prefix);
                        Write(w,"...");
                        WriteLine(w);
                        WriteObject(w,prefix, item);
                    }
                    else
                    {
                        WriteObject(w,prefix, item);
                    }
                }
            }
            else
            {
                MemberInfo[] members = element.GetType().GetMembers(BindingFlags.Public | BindingFlags.Instance);
                foreach (MemberInfo m in members)
                {
                    FieldInfo? f = m as FieldInfo;
                    PropertyInfo? p = m as PropertyInfo;
                    if (f != null || p != null)
                    {
                        Type t = f != null ? f.FieldType : p.PropertyType;
                        if (t.IsValueType || t == typeof(string))
                        {
                            Write(w,prefix);
                            Write(w,m.Name);
                            Write(w,"=");
                            WriteValue(w,f != null ? f.GetValue(element) : p.GetValue(element, null));
                            WriteLine(w);
                        }
                        else
                        {
                            if (typeof(IEnumerable).IsAssignableFrom(t))
                            {
                                //Write("..."); WriteLine();
                            }
                            else
                            {
                                //Write("{ }"); WriteLine();
                            }
                        }
                    }
                }
                foreach (MemberInfo m in members)
                {
                    FieldInfo? f = m as FieldInfo;
                    PropertyInfo? p = m as PropertyInfo;
                    if (f != null || p != null)
                    {
                        Type t = f != null ? f.FieldType : p.PropertyType;
                        if (!(t.IsValueType || t == typeof(string)))
                        {
                            object? value = f != null ? f.GetValue(element) : p.GetValue(element, null);
                            if (value != null)
                            {
                                WriteObject(w,prefix + m.Name + ": ", value);
                            }
                        }
                    }
                }
            }
        }
    }

    private void WriteValue(TextWriter w,object? o)
    {
        if (o == null) {
            Write(w, "null");
        }
        else if (o is DateTime d) {
            Write(w, d.ToShortDateString());
        }
        else if (o is YawPitchRoll ypr)
        {
            Write(w, ypr.Yaw.ToString()); Write(w, ":");
            Write(w, ypr.Pitch.ToString()); Write(w, ":");
            Write(w, ypr.Roll.ToString());
        }
        else if (o is ValueType || o is string)
        {
            Write(w,o.ToString());
        }
        else if (o is TechTreeBitMask ttbm)
        {
            // temporary fix.
            BitArray bol = new(ttbm.bits.Length);
            bol.SetAll(false);
            int idx = 0;
            foreach (bool b in ttbm.bits)
            {
                if (b)
                    bol.Set(((idx / 8) * 8 + (7 - idx % 8)), true);
                idx++;
            }
            // end of fix: to revert replace bol with ttbm.bits
            idx = 0;
            foreach (bool b in bol)
            {
                if (b)
                    WriteValue(w, " " + idx);
                idx++;
            }
        }
        else if (o is IEnumerable)
        {
            Write(w, "...");
        }
        else
        {
            Write(w, "{ }");
        }
    }
}
