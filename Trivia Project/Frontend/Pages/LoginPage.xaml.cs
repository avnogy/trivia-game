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
using System.Windows.Shapes;
using Newtonsoft.Json;
using Frontend.Requests;
using Frontend.Responses;

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
            if (!App.IsInputValidString(usernameTXB.Text))
            {
                MessageBox.Show("username can't be empty and must contain only letters or numbers.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            if (passwordTXB.Password.ToString() == ""||
                passwordTXB.Password.ToString().Contains('\"') || 
                passwordTXB.Password.ToString().Contains('\''))
            {
                MessageBox.Show("password can't contain \" or \'.'", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            LoginRequest loginRequest = new LoginRequest();
            loginRequest.username = usernameTXB.Text;
            loginRequest.password = passwordTXB.Password.ToString();
            string jsonRepr = JsonConvert.SerializeObject(loginRequest);

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