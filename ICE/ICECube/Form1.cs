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
        public Form1()
        {
            InitializeComponent();
        }

        private void btLoad_Click(object sender, EventArgs e)
        {
            if (ofdCore.ShowDialog() == DialogResult.OK)
            {
                IGCCore core = new IGCCore();
                core.Load(ofdCore.FileName);
                IGCLib.DataCivilizationIGC civ;
            }
        }
    }
}
