using Frontend.Requests;
using Frontend.Responses;
using Newtonsoft.Json;
using System;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;

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
            //validating credentials
            if (!Regex.IsMatch(usernameTXB.Text, "^[a-zA-Z0-9]{4,20}$"))
            {
                MessageBox.Show("Invalid username. Usernames must only contain letters or numbers and at least 4 characters long.", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }
            if (!Regex.IsMatch(emailTBX.Text, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"))
            {
                MessageBox.Show("Invalid Email address, Please check the address you entered.", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }
            if (!Regex.IsMatch(passwordTXB.Password.ToString(), "^(?=.{8,}$)(?=.*[0-9]).*$"))
            {
                MessageBox.Show("Invalid password. Passwords must be at least 8 characters long and contain at least one number.", "Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            //creating a json string representation of signup request
            SignupRequest signupRequest = new SignupRequest();
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