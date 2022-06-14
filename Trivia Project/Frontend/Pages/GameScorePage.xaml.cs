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
    /// Interaction logic for GameScorePage.xaml
    /// </summary>
    public partial class GameScorePage : Page
    {
        public GameScorePage(GetGameResultsResponse gameResults)
        {
            InitializeComponent();
            foreach (PlayerResults player in gameResults.results)
            {
                Label label = new Label();
                label.Content = "username: "+ player.username;
                label.FontSize = 24;
                label.FontFamily = new FontFamily("Ink Free");
                label.FontWeight = FontWeights.Bold;
                label.Foreground = new BrushConverter().ConvertFrom("#292929") as Brush;
                if (player.username == App.username)
                {
                    label.Content += "(you)";
                    label.Foreground = new BrushConverter().ConvertFrom("#000000") as Brush;
                }
                if (player.username == gameResults.results.FirstOrDefault().username)
                {
                    //player is the winner
                    label.Foreground = new BrushConverter().ConvertFrom("#C58500") as Brush;
                    label.Content += "(winner)";
                }

                label.Content += "\nscore: " +Math.Round(1000 * ((float)player.correctAnswerCount/
                    (float)((player.wrongAnswerCount + player.averageAnswerTime) == 0 ?
                    1 : ((player.wrongAnswerCount)*3 + player.averageAnswerTime))));
                scoresSP.Children.Add(label);

                if (player.username == App.username)
                {
                    label.Content += "\nright answers: " + player.correctAnswerCount + "\n";
                    label.Content += "wrong answers: " + player.wrongAnswerCount + "\n";
                    label.Content += "average time to answer: " + Math.Round(player.averageAnswerTime,2);
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
