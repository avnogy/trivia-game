using Frontend.Responses;
using Newtonsoft.Json;
using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for GameScorePage.xaml
    /// </summary>
    public partial class GameScorePage : Page
    {
        public GameScorePage(GetGameResultsResponse gameResults)
        {
            InitializeComponent();
            double[] scores = new double[gameResults.results.Count];
            foreach (var item in gameResults.results.Select((player, i) => new { i, player }))
            {
                scores[item.i] = Math.Round(1000 * ((float)item.player.correctAnswerCount /
                    (float)((item.player.wrongAnswerCount + item.player.averageAnswerTime) == 0 ?
                    1 : ((item.player.wrongAnswerCount) * 3 + item.player.averageAnswerTime))));
            }
            foreach (var item in gameResults.results.Select((player, i) => new { i, player }))
            {
                Label label = new Label();
                label.Content = "username: "+ item.player.username;
                label.FontSize = 24;
                label.FontFamily = new FontFamily("Ink Free");
                label.FontWeight = FontWeights.Bold;
                label.Foreground = new BrushConverter().ConvertFrom("#292929") as Brush;
                if (item.player.username == App.username)
                {
                    label.Content += "(you)";
                    label.Foreground = new BrushConverter().ConvertFrom("#000000") as Brush;
                }

                

                label.Content += "\nscore: " +scores[item.i];
                scoresSP.Children.Add(label);

                if (scores[item.i] == scores.Max())
                {
                    //player is the winner
                    label.Foreground = new BrushConverter().ConvertFrom("#C58500") as Brush;
                    label.Content += "(winner)";
                }
                if (item.player.username == App.username)
                {
                    label.Content += "\nright answers: " + item.player.correctAnswerCount + "\n";
                    label.Content += "wrong answers: " + item.player.wrongAnswerCount + "\n";
                    label.Content += "average time to answer: " + Math.Round(item.player.averageAnswerTime, 2);
                }
            }
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            Communicator.Send(Communicator.RequestType.LeaveGameRequest, "");
            StatusResponse response = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (response.status == 0)
            {
                ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
            }
            else
            {
                MessageBox.Show("Fatal:Could not leave the game, Quitting.", "Fatal Error", MessageBoxButton.OK, MessageBoxImage.Error);
                System.Windows.Application.Current.Shutdown();
            }
        }
    }
}