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
    /// Interaction logic for RoomSelectPage.xaml
    /// </summary>
    public partial class RoomSelectPage : Page
    {
        public RoomSelectPage()
        {
            InitializeComponent();
            Communicator.Send(Communicator.RequestType.GetRoomsRequest, "");
            GetRoomsResponse roomsResponse = JsonConvert.DeserializeObject<GetRoomsResponse>(Communicator.Receive());
            foreach (RoomData room in roomsResponse.rooms)
            {
                Label r = new Label();
                r.Content = room.name +" "+ room.maxPlayers;
                r.FontSize = 18;
                r.FontFamily = new FontFamily("Ink Free");
                r.FontWeight = FontWeights.Bold;
                roomsSP.Children.Add(r);
            }
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }
    }
}
