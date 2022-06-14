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
            if (!App.IsInputValidString(nameTBX.Text))
            {
                MessageBox.Show("Room name can't be empty and must contain only letters or numbers.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!App.IsInputValidInt(timeTBX.Text, 1 , 10))
            {
                MessageBox.Show("Time per question must be a valid number between 1 - 10", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!App.IsInputValidInt(amountTBX.Text, 1,10))
            {
                MessageBox.Show("Max mount of players must be a valid number between 1 - 10", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            //creating a json string representation of create room request
            CreateRoomRequest createRequest = new CreateRoomRequest();
            createRequest.roomName = nameTBX.Text;
            createRequest.answerTimeout = int.Parse(timeTBX.Text);
            createRequest.maxUsers = int.Parse(amountTBX.Text);
            createRequest.questionCount = 10; 
            string jsonRepr = JsonConvert.SerializeObject(createRequest);

            //sending create room request
            Communicator.Send(Communicator.RequestType.CreateRoomRequest, jsonRepr);


            //parsing create room response
            StatusResponse signupReponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (signupReponse.status == 0)
            {
                ((MainWindow)Application.Current.MainWindow).frame.Content = new RoomAdminPage(createRequest.roomName, createRequest.answerTimeout, createRequest.maxUsers);
            }
            else
            {
                MessageBox.Show("Couldn't create room, Please try again.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
