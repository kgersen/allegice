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
        public Window1()
        {
            InitializeComponent();

            core = new IGCCore();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.Filter = "IGC Files|*.igc";

            bool? openResult = ofd.ShowDialog(this);
            if (openResult.HasValue && openResult.Value == true)
            {
                core.Load(ofd.FileName);
                
                listView1.ItemsSource = core.m_civilizations;
                listView1.DisplayMemberPath = "name";
                 //Binding b = new Binding();
                //b.Source = core.m_civilizations;
                //b.Path = new PropertyPath("Name");
                //listBox1.SetBinding(ContentProperty, b);
            }
        }
    }
}
