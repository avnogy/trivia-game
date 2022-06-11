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
using System.Threading;
using System.ComponentModel;

namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for RoomPage.xaml
    /// </summary>
    public partial class RoomPage : Page
    {
        const int refreshTime = 3; //seconds
        DispatcherTimer timer;
        BackgroundWorker serverListener = new BackgroundWorker();

        public RoomPage(RoomData room)
        {
            InitializeComponent();
            serverListener.WorkerSupportsCancellation = true;
            serverListener.WorkerReportsProgress = true;
            serverListener.DoWork += listenToServer;
            serverListener.ProgressChanged += handleServerUpdates;

            serverListener.RunWorkerAsync();

            nameTBX.Text += room.name;
            timeTBX.Text += room.timePerQuestion;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(refreshTime);
            timer.Tick += new EventHandler(
                (object? sender, EventArgs? e) => { Communicator.Send(Communicator.RequestType.GetPlayersInRoomRequest, ""); }
                );
            timer.Start();

        }

        private void listenToServer(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                String recv = Communicator.Receive();
                try
                {
                    UpdateResponse updateResponse = JsonConvert.DeserializeObject<UpdateResponse>(recv);
                    serverListener.ReportProgress(updateResponse.type);
                }
                catch (Exception)
                {
                    GetPlayersInRoomResponse roomResponse = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(recv);
                    PopulateRoom(roomResponse, null);
                }
            }
        }

        private void handleServerUpdates(object sender, ProgressChangedEventArgs e)
        {
            switch ((UpdateResponse.Type)e.ProgressPercentage)
            {
                case UpdateResponse.Type.StartGame:
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage(); break;
                case UpdateResponse.Type.LeaveRoom: 
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomSelectPage(); break;
            }
        }

        private void PopulateRoom(object? sender, EventArgs? e)
        {
            GetPlayersInRoomResponse roomResponse = (GetPlayersInRoomResponse)sender;

            if (roomResponse.players != null)
            {
                playersLBL.Content = "players:\n";
                foreach (string player in roomResponse.players)
                {
                    playersLBL.Content += player + "\n";
                }
            }
        }

        private void leaveBTN_Click(object sender, RoutedEventArgs e)
        {
            Communicator.Send(Communicator.RequestType.LeaveRoomRequest, "");
            StatusResponse status = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (status.status == 0)
            {
                timer.Stop();
                ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomSelectPage();
            }
            else
            {
                MessageBox.Show("Couldn't leave room' Please try again.", "Failed", MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }
    }
}
