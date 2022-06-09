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
    /// Interaction logic for RoomPage.xaml
    /// </summary>
    public partial class RoomPage : Page
    {
        const int refreshTime = 2; //seconds
        int roomId;
        public RoomPage(RoomData room)
        {
            InitializeComponent();
            roomId = room.id;
            nameTBX.Text += room.name;
            timeTBX.Text += room.timePerQuestion;

            PopulateRoom(null, null);
            DispatcherTimer timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(refreshTime);
            timer.Tick += new EventHandler(PopulateRoom);
            timer.Start();

        }
        private void PopulateRoom(object? sender, EventArgs? e)
        {
            GetPlayersInRoomRequest getPlayersInRoomRequest = new GetPlayersInRoomRequest();
            getPlayersInRoomRequest.roomId = roomId;
            String jsonRepr = JsonConvert.SerializeObject(getPlayersInRoomRequest);

            Communicator.Send(Communicator.RequestType.GetPlayersInRoomRequest, jsonRepr);
            GetPlayersInRoomResponse playersResponse = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(Communicator.Receive());
            playersLBL.Content = "players:\n";
            foreach (string player in playersResponse.players)
            {
                playersLBL.Content += player + "\n";
            }
        }

        private void leaveBTN_Click(object sender, RoutedEventArgs e)
        {
            Communicator.Send(Communicator.RequestType.LeaveRoomRequest, "");
            StatusResponse status = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (status.status == 0)
            {
                ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomSelectPage();
            }
            else
            {
                MessageBox.Show("Couldn't leave room' Please try again.", "Failed", MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
        }
    }
}
