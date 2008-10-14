using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using IGCLib;

namespace ICECube
{
    public partial class Form1 : Form
    {
        IGCCore core;
        public Form1()
        {
            core = new IGCCore();
            InitializeComponent();
        }

        private void btLoad_Click(object sender, EventArgs e)
        {
            if (ofdCore.ShowDialog() == DialogResult.OK)
            {
                core.Load(ofdCore.FileName);
                listView1.Clear();
                listView1.Items.Add("m_chaffTypes : " + core.m_chaffTypes.Count.ToString());
                listView1.Items.Add("m_civilizations : " + core.m_civilizations.Count.ToString());
                listView1.Items.Add("m_developments : " + core.m_developments.Count.ToString());
                listView1.Items.Add("m_droneTypes : " + core.m_droneTypes.Count.ToString());
                listView1.Items.Add("m_hullTypes : " + core.m_hullTypes.Count.ToString());
                listView1.Items.Add("m_launcherTypes : " + core.m_launcherTypes.Count.ToString());
                listView1.Items.Add("m_mineTypes : " + core.m_mineTypes.Count.ToString());
                listView1.Items.Add("m_missileTypes : " + core.m_missileTypes.Count.ToString());
                listView1.Items.Add("m_partTypes : " + core.m_partTypes.Count.ToString());
                listView1.Items.Add("m_probeTypes : " + core.m_probeTypes.Count.ToString());
                listView1.Items.Add("m_projectileTypes : " + core.m_projectileTypes.Count.ToString());
                listView1.Items.Add("m_stationTypes : " + core.m_stationTypes.Count.ToString());
                listView1.Items.Add("m_treasureSets : " + core.m_treasureSets.Count.ToString());
                listView1.Items.Add("m_projectileTypes : " + core.m_projectileTypes.Count.ToString());
            }
        }

        private void btSave_Click(object sender, EventArgs e)
        {
            core.Save(@"icecubetest.igc");
        }
    }
}
