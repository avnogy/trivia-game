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
    /// Interaction logic for LeaderboardPage.xaml
    /// </summary>
    public partial class LeaderboardPage : Page
    {
        public LeaderboardPage()
        {
            InitializeComponent();
            Communicator.Send(Communicator.RequestType.GetLeaderboardRequest, "");
            string leaderboard = Communicator.Receive();

            LeaderboardResponse statisticsReponse = JsonConvert.DeserializeObject<LeaderboardResponse>(leaderboard);

            //putting stats in the label
            for(int i = 0;i < statisticsReponse.highScore.Count;i+=4)
            {
                statisticsLBL.Content += 
                    statisticsReponse.highScore[i] +
                    "\navrage answer time: " + Math.Round(float.Parse(statisticsReponse.highScore[i+1]),2) +
                    "\ncorrect answers: " + statisticsReponse.highScore[i+2] +
                    "\nplayed games: " + statisticsReponse.highScore[i+3] + "\n";
            }
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new StatisticsPage();
        }
    }
}
