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
    /// Interaction logic for RoomSelectPage.xaml
    /// </summary>
    public partial class RoomSelectPage : Page
    {
        const int refreshTime = 2; //seconds
        DispatcherTimer timer;
        public RoomSelectPage()
        {
            InitializeComponent();
            PopulateRoom(null,null);

            //timer refreshes rooms
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(refreshTime);
            timer.Tick += new EventHandler(PopulateRoom);
            timer.Start();
        }
        private void PopulateRoom(object? sender, EventArgs? e)
        {
            Communicator.Send(Communicator.RequestType.GetRoomsRequest, "");
            GetRoomsResponse roomsResponse = JsonConvert.DeserializeObject<GetRoomsResponse>(Communicator.Receive());

            roomsSP.Children.Clear();
            if (roomsResponse.rooms != null)
            {
                foreach (RoomData room in roomsResponse.rooms)
                {
                    if (room.isActive == true)
                    {
                        GetPlayersInRoomRequest getPlayersInRoomRequest = new GetPlayersInRoomRequest();
                        getPlayersInRoomRequest.roomId = room.id;
                        string jsonRepr = JsonConvert.SerializeObject(getPlayersInRoomRequest);

                        Communicator.Send(Communicator.RequestType.GetPlayersInRoomRequest, jsonRepr);
                        GetPlayersInRoomResponse roomResponse = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(Communicator.Receive());

                        if (roomResponse.players != null)
                        {
                            Label r = new Label();
                            r.Content = room.name +" ("+roomResponse.players.Count+"/"+room.maxPlayers+")";
                            r.FontSize = 18;
                            r.FontFamily = new FontFamily("Ink Free");
                            r.FontWeight = FontWeights.Bold;
                            r.Tag = room;
                            r.MouseUp += (x, y) =>
                            {
                                JoinRoomRequest joinRoomRequest = new JoinRoomRequest();
                                joinRoomRequest.roomId = room.id;
                                string jsonRepr = JsonConvert.SerializeObject(joinRoomRequest);
                                Communicator.Send(Communicator.RequestType.JoinRoomRequest, jsonRepr);
                                StatusResponse statusResponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
                                if (statusResponse.status == 0)
                                {
                                    timer.Stop();
                                    ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomPage((RoomData)(r.Tag));
                                }
                                else
                                {
                                    MessageBox.Show("Can't join room.", "Failed", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                                }
                            };
                            roomsSP.Children.Add(r);
                        }
                    }
                }
            }
            if (roomsSP.Children.Count == 0)
            {
                Label r = new Label();
                r.Content = "There are no active rooms.. :(";
                r.FontSize = 18;
                r.FontFamily = new FontFamily("Ink Free");
                r.FontWeight = FontWeights.Bold;
                r.Foreground = new BrushConverter().ConvertFrom("#FF505050") as SolidColorBrush;
                roomsSP.Children.Add(r);
            }
        }
        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }
    }
}
