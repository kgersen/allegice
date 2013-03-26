//Copyright (C) Microsoft Corporation.  All rights reserved.
// kgersen = heavily modified to "flatten" and "single line"ing the output
using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using IGCLib;

// See the ReadMe.html for additional information
public class ObjectDumper {

    public static void Write(string prefix, object element)
    {
        Write(prefix, element, Console.Out);
    }

    public static void Write(string prefix, object element, TextWriter log)
    {
        ObjectDumper dumper = new ObjectDumper();
        dumper.writer = log;
        dumper.WriteObject(prefix, element);
    }

    TextWriter writer;
    int pos;

    private ObjectDumper()
    {
    }

    private void Write(string s)
    {
        if (s != null) {
            writer.Write(s);
            pos += s.Length;
        }
    }

    private void WriteLine()
    {
        writer.WriteLine();
        pos = 0;
    }

    private void WriteTab()
    {
        Write("  ");
        while (pos % 8 != 0) Write(" ");
    }

    private void WriteObject(string prefix, object element)
    {
        if (element == null || element is ValueType || element is string || element is TechTreeBitMask) {
            Write(prefix);
            WriteValue(element);
            WriteLine();
        }
        else
        {
            IEnumerable enumerableElement = element as IEnumerable;
            if (enumerableElement != null)
            {
                foreach (object item in enumerableElement)
                {
                    if (item is IEnumerable && !(item is string))
                    {
                        Write(prefix);
                        Write("...");
                        WriteLine();
                        WriteObject(prefix, item);
                    }
                    else
                    {
                        WriteObject(prefix, item);
                    }
                }
            }
            else
            {
                MemberInfo[] members = element.GetType().GetMembers(BindingFlags.Public | BindingFlags.Instance);
                foreach (MemberInfo m in members)
                {
                    FieldInfo f = m as FieldInfo;
                    PropertyInfo p = m as PropertyInfo;
                    if (f != null || p != null)
                    {
                        Type t = f != null ? f.FieldType : p.PropertyType;
                        if (t.IsValueType || t == typeof(string))
                        {
                            Write(prefix);
                            Write(m.Name);
                            Write("=");
                            WriteValue(f != null ? f.GetValue(element) : p.GetValue(element, null));
                            WriteLine();
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
                    FieldInfo f = m as FieldInfo;
                    PropertyInfo p = m as PropertyInfo;
                    if (f != null || p != null)
                    {
                        Type t = f != null ? f.FieldType : p.PropertyType;
                        if (!(t.IsValueType || t == typeof(string)))
                        {
                            object value = f != null ? f.GetValue(element) : p.GetValue(element, null);
                            if (value != null)
                            {
                                WriteObject(prefix + m.Name + ": ", value);
                            }
                        }
                    }
                }
            }
        }
    }

    private void WriteValue(object o)
    {
        if (o == null) {
            Write("null");
        }
        else if (o is DateTime) {
            Write(((DateTime)o).ToShortDateString());
        }
        else if (o is ValueType || o is string) {
            Write(o.ToString());
        }
        else if (o is TechTreeBitMask)
        {
            TechTreeBitMask ttbm = (TechTreeBitMask)o;

            // temporary fix.
            BitArray bol = new BitArray(ttbm.bits.Length);
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
                    WriteValue(" " + idx);
                idx++;
            }
        }
        else if (o is IEnumerable)
        {
            Write("...");
        }
        else
        {
            Write("{ }");
        }
    }
}
