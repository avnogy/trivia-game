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
            LoginRequest loginRequest = new LoginRequest();
            loginRequest.username = usernameTXB.Text;
            loginRequest.password = passwordTXB.Password.ToString();
            String jsonRepr = JsonConvert.SerializeObject(loginRequest);

            //sending signup request
            Communicator.Send(Communicator.RequestType.LoginRequest, jsonRepr);

            //parsing signup response
            LoginResponse loginReponse = JsonConvert.DeserializeObject<LoginResponse>(Communicator.Receive());
            if (loginReponse != null && loginReponse.status == 0)
            {
                this.switchToMenu();
            }
            else
            {
                MessageBox.Show("Your username or password are incorrect, Please try again.", "Invalid Credentials", MessageBoxButton.OK, MessageBoxImage.Error);
                /*Label errorLabel = new Label();
                errorLabel.Name = "LabelError";
                errorLabel.Content = "You're not signed up yet.";
                errorLabel.Margin = new Thickness(30, 0, 30, 0);
                errorLabel.VerticalAlignment = VerticalAlignment.Bottom;
                errorLabel.HorizontalContentAlignment = HorizontalAlignment.Center;
                errorLabel.Foreground = Brushes.Black;
                errorLabel.Background = new SolidColorBrush(Color.FromArgb(0xFF, 0xFF, 0xCF, 0xCF));
                errorLabel.FontFamily = new FontFamily("Bell MT");
                errorLabel.FontSize = 12.5;

                Grid.SetRow(errorLabel, 0);
                Grid.SetColumnSpan(errorLabel, 3);
                Grid.Children.Add(errorLabel);*/
            }
        }
    }
}