using Frontend.Responses;
using Newtonsoft.Json;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Threading;

namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for RoomAdminPage.xaml
    /// </summary>
    public partial class RoomAdminPage : Page
    {
        private const int refreshTime = 2; //seconds
        private int timeToAnswer;
        private DispatcherTimer timer;

        public RoomAdminPage(string roomName, int timePerQuestion, int maxPlayers)
        {
            InitializeComponent();
            timeToAnswer = timePerQuestion;

            nameTBX.Text += roomName;
            timeTBX.Text += timePerQuestion;
            amountTBX.Text += maxPlayers;

            PopulateRoom(null, null);
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
            ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage(timeToAnswer);
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