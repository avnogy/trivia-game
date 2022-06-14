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
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupPage : Page
    {
        public SignupPage()
        {
            InitializeComponent();
        }

        private void switchToLogin()
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new LoginPage();
        }

        private void buttonLogin_Click(object sender, RoutedEventArgs e)
        {
            this.switchToLogin();
        }

        private void buttonSubmit_Click(object sender, RoutedEventArgs e)
        {
            //creating a json string representation of signup request
            SignupRequest signupRequest = new SignupRequest();
            if (!App.IsInputValidString(usernameTXB.Text))
            {
                MessageBox.Show("username can't be empty and must contain only letters or numbers.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            if (!emailTBX.Text.Contains('@') || emailTBX.Text.Contains('\"') ||
                emailTBX.Text.Contains('\''))
            {
                MessageBox.Show("email adress must be valid.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            if (passwordTXB.Password.ToString() == ""||
                passwordTXB.Password.ToString().Contains('\"') ||
                passwordTXB.Password.ToString().Contains('\''))
            {
                MessageBox.Show("password can't contain \" or \'.'", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            signupRequest.username = usernameTXB.Text;
            signupRequest.password = passwordTXB.Password.ToString();
            signupRequest.email    = emailTBX.Text;
            String jsonRepr = JsonConvert.SerializeObject(signupRequest);

            //sending signup request
            Communicator.Send(Communicator.RequestType.SignupRequest, jsonRepr);

            //parsing signup response
            StatusResponse signupReponse = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (signupReponse.status == 0)
            {
                this.switchToLogin();
            }
            else
            {
                MessageBox.Show("You've already signed up.", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }
    }
}