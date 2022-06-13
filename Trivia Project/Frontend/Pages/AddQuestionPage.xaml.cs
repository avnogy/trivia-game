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
    /// Interaction logic for AddQuestion.xaml
    /// </summary>
    public partial class AddQuestionPage : Page
    {
        public AddQuestionPage()
        {
            InitializeComponent();
        }

        private void backBTN_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).frame.Content = new MenuPage();
        }

        private void submitBTN_Click(object sender, RoutedEventArgs e)
        {
            if (questionTBX.Text == "" || rightAnswerTBX.Text == "" ||
                wrongAnswer1TBX.Text == "" || wrongAnswer2TBX.Text == "" ||
                wrongAnswer3TBX.Text == "")
            {
                MessageBox.Show("Fields can't be empty.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            AddQuestionRequest request = new AddQuestionRequest();

            request.question = questionTBX.Text;
            request.possibleAnswers = new List<string>();
            request.possibleAnswers.Add(wrongAnswer1TBX.Text);
            request.possibleAnswers.Add(wrongAnswer2TBX.Text);
            request.possibleAnswers.Add(wrongAnswer3TBX.Text);
            request.correctAnswer = rightAnswerTBX.Text;

            string jsonRepr = JsonConvert.SerializeObject(request);
            Communicator.Send(Communicator.RequestType.AddQuestionRequest, jsonRepr);

            StatusResponse response = JsonConvert.DeserializeObject<StatusResponse>(Communicator.Receive());
            if (response.status == 0)
            {
                MessageBox.Show("Your question was added to the database.", "Success", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                ((MainWindow)Application.Current.MainWindow).frame.Content = new AddQuestionPage();
            }
            else
            {
                MessageBox.Show("Error, Couldnt add question to the database, try again later.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
