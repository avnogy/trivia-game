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
        int timeToAnswer;
        const int refreshTime = 2; //seconds
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

            timeToAnswer = room.timePerQuestion;
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
                if (serverListener.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                //receive message from server
                if (Communicator.IsDataAvailable())
                {
                    String recv = Communicator.Receive();

                    //try to parse message
                    UpdateResponse updateResponse = JsonConvert.DeserializeObject<UpdateResponse>(recv);

                    //if message has not parsed correctly
                    if (updateResponse.status == 0)
                    {
                        //parse message again
                        GetPlayersInRoomResponse roomResponse = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(recv);

                        //update population
                        serverListener.ReportProgress(3, roomResponse);
                    }
                    else
                    {
                        //try to start/leave room
                        timer.Stop();
                        serverListener.ReportProgress(updateResponse.type, null);
                        break;
                    }
                }
            }
        }

        private void handleServerUpdates(object sender, ProgressChangedEventArgs e)
        {
            switch ((UpdateResponse.Type)e.ProgressPercentage)
            {
                case UpdateResponse.Type.StartGame:
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage(timeToAnswer); break;

                case UpdateResponse.Type.LeaveRoom:
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomSelectPage(); break;

                case (UpdateResponse.Type)3:
                    {
                        GetPlayersInRoomResponse roomResponse = (GetPlayersInRoomResponse)e.UserState;
                        if (roomResponse.players != null)
                        {
                            playersLBL.Content = "players:\n";
                            foreach (string player in roomResponse.players)
                            {
                                playersLBL.Content += player + "\n";
                            }
                        }
                    }
                    break;
                    //PopulateRoom((GetPlayersInRoomResponse)e.UserState); break;
            }
        }

        private void PopulateRoom(GetPlayersInRoomResponse roomResponse)
        {
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
            timer.Stop();
            serverListener.CancelAsync();

            Communicator.Send(Communicator.RequestType.LeaveRoomRequest, "");
            StatusResponse status = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());

            ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomSelectPage();
        }
    }
}
