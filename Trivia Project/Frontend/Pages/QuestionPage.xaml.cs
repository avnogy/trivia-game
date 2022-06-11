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
using Frontend.Requests;
using Frontend.Responses;
using Newtonsoft.Json;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for QuestionPage.xaml
    /// </summary>
    public partial class QuestionPage : Page
    {
        private Button[] buttons;
        private int selectedButtonIndex;

        public QuestionPage()
        {
            InitializeComponent();

            //getting question and answers from server
            Communicator.Send(Communicator.RequestType.GetQuestionRequest, "");
            GetQuestionResponse response = JsonConvert.DeserializeObject<GetQuestionResponse>(Communicator.Receive());
            questionLBL.Content = response.question;
            choiceTopLeftBTN.Content = response.possibleAnswers[0];
            choiceTopRightBTN.Content = response.possibleAnswers[1];
            choiceBottomLeftBTN.Content = response.possibleAnswers[2];
            choiceBottomRightBTN.Content = response.possibleAnswers[3];

            //initiating buttins
            this.buttons = new Button[4];
            this.buttons[0] = choiceTopLeftBTN;
            this.buttons[1] = choiceTopRightBTN;
            this.buttons[2] = choiceBottomLeftBTN;
            this.buttons[3] = choiceBottomRightBTN;
        }

        private void select(int buttonIndex)
        {
            for (int i = 0; i < this.buttons.Length; i++)
            {
                if (i == buttonIndex) continue;
                this.buttons[i].Background = new BrushConverter().ConvertFrom("#98c9f0") as SolidColorBrush;
            }

            this.buttons[buttonIndex].Background = new BrushConverter().ConvertFrom("#FEE253") as SolidColorBrush;
            this.selectedButtonIndex = buttonIndex;
        }

        private void markCorrectAsnwer(String correctAnswer)
        {
            if (correctAnswer == this.buttons[this.selectedButtonIndex].Content.ToString())
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
            }
            else
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#eb8496") as SolidColorBrush;
                foreach(ref Button button in this.buttons.AsSpan())
                {
                    if (button.Content.ToString() == correctAnswer)
                    {
                        button.Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
                        break;
                    }
                }
            }
        }

        private void choiceTopLeftBTN_Click(object sender, RoutedEventArgs e)
        {
            select(0);
        }

        private void choiceTopRightBTN_Click(object sender, RoutedEventArgs e)
        {
            select(1);
        }

        private void choiceBottomLeftBTN_Click(object sender, RoutedEventArgs e)
        {
            select(2);
        }

        private void choiceBottomRightBTN_Click(object sender, RoutedEventArgs e)
        {
            select(3);
        }

        private void submitBTN_Click(object sender, RoutedEventArgs e)
        {
            String selectedAnswer = this.buttons[this.selectedButtonIndex].Content.ToString();

            SubmitAnswerRequest submitRequest;
            submitRequest.answer = selectedAnswer;

            String jsonRepr = JsonConvert.SerializeObject(submitRequest);
            Communicator.Send(Communicator.RequestType.SubmitAnswerRequest, jsonRepr);

            SubmitAnswerResponse submitResponse = JsonConvert.DeserializeObject<SubmitAnswerResponse>(Communicator.Receive());
            markCorrectAsnwer(submitResponse.correctAnswer);
        }
    }
}
