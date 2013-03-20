using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IGCLib;
using System.Reflection;

namespace CoreDump
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.Out.Write("error: no argument");
                return;
            }
            IGCCore core = new IGCCore();
            core.Load(args[0]);
            
            //TODO: fancy print GAs attributes and other array values

            ObjectDumper.Write("Globals-",core.Constants);

            foreach (DataCivilizationIGC civ in core.m_civilizations)
            {
                string civid = "Factions-" + civ.name + "(" + civ.civilizationID+ ")-";
                ObjectDumper.Write(civid,civ);
            }
            foreach (DataDevelopmentIGC dev in core.m_developments)
            {
                string devid = "Devels-"+dev.name+"("+dev.developmentID+")-";
                ObjectDumper.Write(devid, dev);
            }
            foreach (DataDroneTypeIGC d in core.m_droneTypes)
            {
                string did = "Drones-" + d.name + " (" + d.droneTypeID + ")-";
                ObjectDumper.Write(did, d);
            }
            foreach (DataProjectileTypeIGC p in core.m_projectileTypes)
            {
                string pid = "Projectiles-p#" + p.projectileTypeID +"-";
                ObjectDumper.Write(pid, p);
            }
            foreach (DataStationTypeIGC s in core.m_stationTypes)
            {
                string sid = "Stations-" + s.name + "(" + s.stationTypeID + ")-";
                ObjectDumper.Write(sid, s);
            }
            foreach (DataHullTypeIGC h in core.m_hullTypes)
            {
                string hid = "Ships-" + h.name + "(" + h.hullID + ")-";
                ObjectDumper.Write(hid, h);
            }
            foreach (DataPartTypeIGC p in core.m_partTypes)
            {
                string pid = "Parts-" + p.name + "(" + p.partID + ")-";
                ObjectDumper.Write(pid, p);
            }
            foreach (DataTreasureSetIGC t in core.m_treasureSets)
            {
                string tid = "Treasures-" + t.name + "(" + t.treasureSetID + ")-";
                ObjectDumper.Write(tid, t);
            }
        }
    }
}
