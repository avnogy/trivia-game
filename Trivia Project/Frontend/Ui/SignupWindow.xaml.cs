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

        private void buttonLogin_Click(object sender, RoutedEventArgs e)
        {
            this.switchToLogin();
        }

        private void buttonSubmit_Click(object sender, RoutedEventArgs e)
        {
            //creating a json string representation of signup request
            SignupRequest signupRequest = new SignupRequest();
            signupRequest.username = textboxUsername.Text;
            signupRequest.password = textboxPassword.Text;
            signupRequest.email    = textboxEmail.Text;
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
                errorLabel.Name = "LabelError";
                errorLabel.Content = "You've already signed up.";
                errorLabel.Margin = new Thickness(30, 0, 30, 0);
                errorLabel.VerticalAlignment = VerticalAlignment.Bottom;
                errorLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                errorLabel.Foreground = Brushes.Black;
                errorLabel.Background = new SolidColorBrush(Color.FromArgb(0xFF, 0xFF, 0xCF, 0xCF));
                errorLabel.FontFamily = new FontFamily("Bell MT");
                errorLabel.FontSize = 12.5;

                Grid.SetRow(errorLabel, 0);
                Grid.SetColumnSpan(errorLabel, 3);
                Grid.Children.Add(errorLabel); 
            }
        }
    }
}