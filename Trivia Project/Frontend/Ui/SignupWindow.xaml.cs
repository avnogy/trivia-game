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

namespace Frontend
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        public SignupWindow()
        {
            InitializeComponent();
        }

        private void switchToLogin()
        {
            this.Hide();

            Window loginWindow = new LoginWindow();
            loginWindow.ShowDialog();

            this.Close();
        }

        private void buttonSignupLogin_Click(object sender, RoutedEventArgs e)
        {
            this.switchToLogin();
        }

        private void buttonSignupSubmit_Click(object sender, RoutedEventArgs e)
        {
            //creating a json string representation of signup request
            SignupRequest signupRequest = new SignupRequest();
            signupRequest.username = textboxSignupUsername.Text;
            signupRequest.password = textboxSignupPassword.Text;
            signupRequest.email    = textboxSignupEmail.Text;
            String jsonRepr = JsonConvert.SerializeObject(signupRequest);

            //sending signup request
            Communicator.Send(Communicator.RequestType.SignupRequest, jsonRepr);

            //parsing signup response
            SignupResponse signupReponse = JsonConvert.DeserializeObject<SignupResponse>(Communicator.Receive());
            if (signupReponse.status == 0)
            {
                this.switchToLogin();
            }
            else
            {
                Label errorLabel = new Label();
                errorLabel.Name = "labelSignupError";
                errorLabel.Content = "Couldn't Signup!";
                errorLabel.Foreground = new SolidColorBrush(Color.FromRgb(204, 73, 73));
                errorLabel.FontFamily = new FontFamily("Bell MT");
                errorLabel.FontSize = 12;
                errorLabel.Width = 126;
                errorLabel.HorizontalAlignment = HorizontalAlignment.Center;
                errorLabel.VerticalAlignment = VerticalAlignment.Top;

                Grid.SetRow(errorLabel, 9);
                Grid.SetRowSpan(errorLabel, 2);
                Grid.SetColumn(errorLabel, 1);
                Grid.SetColumnSpan(errorLabel, 2);
                Grid.Children.Add(errorLabel); 
            }
        }
    }
}