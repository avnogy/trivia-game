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

            if (!int.TryParse(timeTBX.Text, out int timePerQuestion)) { MessageBox.Show("Time per question must be a valid number", "Error", MessageBoxButton.OK, MessageBoxImage.Error); return; }

            if (timePerQuestion > 10 || timePerQuestion < 1) { MessageBox.Show("Time per question must be between 1 and 10 minutes", "Error", MessageBoxButton.OK, MessageBoxImage.Error); return; }

            if (!int.TryParse(amountTBX.Text, out int amountOfPlayers)) { MessageBox.Show("Amount of players must be a valid number", "Error", MessageBoxButton.OK, MessageBoxImage.Error); return; }

            if (amountOfPlayers > 10 || amountOfPlayers < 1) { MessageBox.Show("Amount of players must be between 1 and 10", "Error", MessageBoxButton.OK, MessageBoxImage.Error); return; }

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
            SignupResponse signupReponse = JsonConvert.DeserializeObject<SignupResponse>(Communicator.Receive());
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
