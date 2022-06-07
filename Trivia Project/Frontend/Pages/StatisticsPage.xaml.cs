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
            Communicator.Send(Communicator.RequestType.GetStatisticsRequest, "");
            StatisticsResponse statisticsReponse = JsonConvert.DeserializeObject<StatisticsResponse>(Communicator.Receive());

            //putting stats in the label
            statisticsLBL.Content += "avrage answer time: " + statisticsReponse.statistics[0].Split('.')[0] + "." + statisticsReponse.statistics[0].Split('.')[1].Substring(0, 2) + "\n\n";
            statisticsLBL.Content += "correct answers: " + statisticsReponse.statistics[1] + "\n\n";
            statisticsLBL.Content += "total answers: " + statisticsReponse.statistics[2] + "\n\n";
            statisticsLBL.Content += "played games: " + statisticsReponse.statistics[3] + "\n\n";
            statisticsLBL.Content += "right answers ratio: " + Math.Round(float.Parse(statisticsReponse.statistics[1])/ float.Parse(statisticsReponse.statistics[2]),2);
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }

        private void leaderboardBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new LeaderboardPage();
        }
    }
}
