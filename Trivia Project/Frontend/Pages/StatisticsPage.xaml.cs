using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;
using Frontend.Requests;
using Frontend.Responses;

namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for StatisticsPage.xaml
    /// </summary>
    public partial class StatisticsPage : Page
    {
        public StatisticsPage()
        {
            InitializeComponent();
            //Communicator.Send(Communicator.RequestType.GetStatisticsRequest, "");
            //StatisticsResponse statisticsReponse = JsonConvert.DeserializeObject<StatisticsResponse>(Communicator.Receive());
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }

        private void leaderboardBTN_Click(object sender, RoutedEventArgs e)
        {
            //((MainWindow)Application.Current.MainWindow).frame.Content = new LeaderboardPage();
        }
    }
}
