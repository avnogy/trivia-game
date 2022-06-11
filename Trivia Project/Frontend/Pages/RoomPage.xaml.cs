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
            //ThreadStart target = new ThreadStart(listenToServer);
            serverListener.WorkerSupportsCancellation = true;
            serverListener.WorkerReportsProgress = true;
            serverListener.DoWork += listenToServer;
            serverListener.ProgressChanged += loadQuestionPage;

            serverListener.RunWorkerAsync();


            nameTBX.Text += room.name;
            timeTBX.Text += room.timePerQuestion;

            //PopulateRoom(null, null);
            //timer = new DispatcherTimer();
            //timer.Interval = TimeSpan.FromSeconds(refreshTime);
            //timer.Tick += new EventHandler(PopulateRoom);
            //timer.Start();

        }

        private void listenToServer(object sender, DoWorkEventArgs e)
        {
            StatusResponse serverResponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            serverListener.ReportProgress(0);
        }

        private void loadQuestionPage(object sender, ProgressChangedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage();
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
