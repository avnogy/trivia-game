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
    /// Interaction logic for RoomAdminPage.xaml
    /// </summary>
    public partial class RoomAdminPage : Page
    {
        public RoomAdminPage(string roomName,int timePerQuestion, int maxPlayers)
        {
            InitializeComponent();
            nameTBX.Text += roomName;
            timeTBX.Text += timePerQuestion;
            amountTBX.Text += maxPlayers;
        }

        private void startBTN_Click(object sender, RoutedEventArgs e)
        {
            //TO:DO: start a game here
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            Communicator.Send(Communicator.RequestType.CloseRoomRequest, "");
            StatusResponse statisticsReponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            ((MainWindow)Application.Current.MainWindow).frame.Content = new CreateRoomPage();
        }
    }
}
