using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using IGCLib;

namespace ICE3
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        IGCCore core;
        IGCMap map;
        public Window1()
        {
            InitializeComponent();

            core = new IGCCore();
            map = new IGCMap();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.Filter = "IGC Files|*.igc";

            bool? openResult = ofd.ShowDialog(this);
            if (openResult.HasValue && openResult.Value == true)
            {
                core.Load(ofd.FileName);

                GridView gv = new GridView();
                GridViewColumn gvc;
                
                // 100% dynamic binding with no predef xaml

                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("civilizationID");
                gvc.Header = "ID";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("name");
                gvc.Header = "Name";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("bonusMoney");
                gvc.Header = "Bonus Money";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("incomeMoney");
                gvc.Header = "Income Money";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("hudName");
                gvc.Header = "HUD name";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("initialStationTypeID");
                gvc.Header = "Starting Station";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("lifepod");
                gvc.Header = "Lifepod";
                gv.Columns.Add(gvc);

                listView1.View = gv;
                listView1.ItemsSource = core.m_civilizations;

                //listView1.DisplayMemberPath = "name";
                //listView1.ItemTemplate = (DataTemplate)Resources["civFormating"];
                //Binding b = new Binding();
                //b.Source = core.m_civilizations;
                //b.Path = new PropertyPath("Name");
                //listBox1.SetBinding(ContentProperty, b);
            }
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.Filter = "IGC Files|*.igc";

            bool? openResult = ofd.ShowDialog(this);
            if (openResult.HasValue && openResult.Value == true)
            {
                map.Load(ofd.FileName);

                GridView gv = new GridView();
                GridViewColumn gvc;

                // 100% dynamic binding with no predef xaml

                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("clusterID");
                gvc.Header = "ID";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("name");
                gvc.Header = "Name";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("posterName");
                gvc.Header = "Poster";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("screenX");
                gvc.Header = "X";
                gv.Columns.Add(gvc);
                gvc = new GridViewColumn();
                gvc.DisplayMemberBinding = new Binding("screenY");
                gvc.Header = "Y";
                gv.Columns.Add(gvc);

                listView1.View = gv;
                listView1.ItemsSource = map.m_clusters;
            }
        }
    }
}
