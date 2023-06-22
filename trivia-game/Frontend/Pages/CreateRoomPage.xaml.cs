using Frontend.Requests;
using Frontend.Responses;
using Newtonsoft.Json;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;

namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for createRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : Page
    {
        public CreateRoomPage()
        {
            InitializeComponent();
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }

        private void createBTN_Click(object sender, RoutedEventArgs e)
        {
            //checking validity of fields
            if (nameTBX.Text == "") { MessageBox.Show("Room name can't be empty.", "Error", MessageBoxButton.OK, MessageBoxImage.Error); return; }

            if (!Regex.IsMatch(timeTBX.Text, "^(?:[1-9]|10)$") || !int.TryParse(timeTBX.Text, out int timePerQuestion)) { MessageBox.Show("Time per question must be a valid number between 1 and 10.", "Error", MessageBoxButton.OK, MessageBoxImage.Error); return; }

            if (!Regex.IsMatch(amountTBX.Text, "^(?:[1-9]|10)$") || !int.TryParse(amountTBX.Text, out int amountOfPlayers)) { MessageBox.Show("Amount of players must be a valid number between 1 and 10.", "Error", MessageBoxButton.OK, MessageBoxImage.Error); return; }

            //creating a json string representation of create room request
            CreateRoomRequest createRequest = new CreateRoomRequest();
            createRequest.roomName = nameTBX.Text;
            createRequest.answerTimeout = timePerQuestion;
            createRequest.maxUsers = amountOfPlayers;
            createRequest.questionCount = 10; //could change later to give user choice
            string jsonRepr = JsonConvert.SerializeObject(createRequest);

            //sending create room request
            Communicator.Send(Communicator.RequestType.CreateRoomRequest, jsonRepr);

            //parsing create room response
            StatusResponse signupReponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (signupReponse.status == 0)
            {
                ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomAdminPage(nameTBX.Text, timePerQuestion, amountOfPlayers);
            }
            else
            {
                MessageBox.Show("Couldn't create room, Please try again.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}