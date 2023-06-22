using Frontend.Responses;
using Newtonsoft.Json;
using System;
using System.Windows;
using System.Windows.Controls;

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
            LeaderboardResponse statisticsReponse = JsonConvert.DeserializeObject<LeaderboardResponse>(Communicator.Receive());

            //putting stats in the label
            for (int i = 0; i < statisticsReponse.highScore.Count; i+=4)
            {
                statisticsLBL.Content +=
                    statisticsReponse.highScore[i] +
                    "\navrage answer time: " + Math.Round(float.Parse(statisticsReponse.highScore[i+1]), 2) +
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