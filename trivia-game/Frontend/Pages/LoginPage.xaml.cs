using Frontend.Requests;
using Frontend.Responses;
using Newtonsoft.Json;
using System;
using System.Windows;
using System.Windows.Controls;

namespace Frontend.Pages
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginPage : Page
    {
        public LoginPage()
        {
            InitializeComponent();
        }

        private void switchToSignup()
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new SignupPage();
        }

        private void switchToMenu()
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }

        private void buttonSignup_Click(object sender, RoutedEventArgs e)
        {
            this.switchToSignup();
        }

        private void buttonSubmit_Click(object sender, RoutedEventArgs e)
        {
            //creating a json string representation of signup request
            LoginRequest loginRequest = new LoginRequest();
            loginRequest.username = usernameTXB.Text;
            loginRequest.password = passwordTXB.Password.ToString();
            String jsonRepr = JsonConvert.SerializeObject(loginRequest);

            //sending signup request
            Communicator.Send(Communicator.RequestType.LoginRequest, jsonRepr);

            //parsing signup response
            StatusResponse loginReponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (loginReponse.status == 0)
            {
                App.username = loginRequest.username;
                this.switchToMenu();
            }
            else
            {
                MessageBox.Show("Your username or password are incorrect, Please try again.", "Invalid Credentials", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}