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
using System.Windows.Threading;
namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for RoomAdminPage.xaml
    /// </summary>
    public partial class RoomAdminPage : Page
    {
        const int refreshTime = 2; //seconds
        DispatcherTimer timer;
        public RoomAdminPage(string roomName,int timePerQuestion, int maxPlayers)
        {
            InitializeComponent();
            nameTBX.Text += roomName;
            timeTBX.Text += timePerQuestion;
            amountTBX.Text += maxPlayers;

            PopulateRoom(null,null);
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(refreshTime);
            timer.Tick += new EventHandler(PopulateRoom);
            timer.Start();
        }
        private void PopulateRoom(object? sender, EventArgs? e)
        {
            Communicator.Send(Communicator.RequestType.GetPlayersInRoomRequest, "");
            GetPlayersInRoomResponse roomResponse = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(Communicator.Receive());
            
            if (roomResponse.players != null)
            {
                playersLBL.Content = "players:\n";
                foreach (string player in roomResponse.players)
                {
                    playersLBL.Content += player + "\n";
                }
            }
        }

        private void startBTN_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            Communicator.Send(Communicator.RequestType.StartGameRequest, "");
            StatusResponse startGameResponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage();
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            Communicator.Send(Communicator.RequestType.CloseRoomRequest, "");
            StatusResponse statisticsReponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            ((MainWindow)Application.Current.MainWindow).frame.Content = new CreateRoomPage();
        }
    }
}
