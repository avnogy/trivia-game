using Frontend.Pages;
using Frontend.Requests;
using Frontend.Responses;
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Threading;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for QuestionPage.xaml
    /// </summary>
    public partial class QuestionPage : Page
    {
        private int timeToAnswer;
        private Button[] buttons;
        private int selectedButtonIndex = 4;
        private BackgroundWorker serverListener = new BackgroundWorker();
        private DispatcherTimer timer = new DispatcherTimer();
        private Stopwatch answerTime;
        private Mutex receiveMtx = new Mutex();

        private void initializeTimer()
        {
            answerTime = Stopwatch.StartNew();
            timeLBL.Content = timeToString(timeToAnswer * 60); //converting minutes and updating label
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += (sender, args) =>
            {
                int totalSecondsLeft = timeToSeconds(timeLBL.Content.ToString()) - 1; //convert + tick
                timeLBL.Content = timeToString(totalSecondsLeft); //updating label
                if (totalSecondsLeft <= 0)
                {
                    submitBTN_Click(null, null);
                }
            };
            timer.Start();
        }

        /// <summary>
        /// returns time in seconds
        /// </summary>
        /// <param name="time"></param>
        /// <returns></returns>
        private int timeToSeconds(string time)
        {
            try
            {
                int minutesLeft = int.Parse(time.Split(':')[0]);
                int secondsLeft = int.Parse(time.Split(':')[1]);
                return minutesLeft * 60 + secondsLeft;
            }
            catch (Exception)
            {
                return -1;
            }
        }

        /// <summary>
        /// returns time in the shape of 00:00
        /// </summary>
        /// <param name="seconds"></param>
        /// <returns></returns>
        private string timeToString(int seconds)
        {
            return "0" + seconds / 60 + ":" + ((seconds % 60 >= 10) ? seconds % 60 : "0" + seconds % 60);
        }

        private void initializeServerListener()
        {
            serverListener.WorkerSupportsCancellation = true;
            serverListener.WorkerReportsProgress = true;
            serverListener.DoWork += listenToServer;
            serverListener.ProgressChanged += handleServerMessages;
        }

        private void initializeComponents(GetQuestionResponse response)
        {
            questionLBL.Content = response.question;
            choiceTopLeftBTN.Content = response.possibleAnswers[0];
            choiceTopRightBTN.Content = response.possibleAnswers[1];
            choiceBottomLeftBTN.Content = response.possibleAnswers[2];
            choiceBottomRightBTN.Content = response.possibleAnswers[3];

            //initiating buttins
            this.buttons = new Button[5];
            this.buttons[0] = choiceTopLeftBTN;
            this.buttons[1] = choiceTopRightBTN;
            this.buttons[2] = choiceBottomLeftBTN;
            this.buttons[3] = choiceBottomRightBTN;
            this.buttons[4] = new Button { Content = "wrong answer for sure" };
        }

        public QuestionPage(int timeToAnswer)
        {
            this.timeToAnswer = timeToAnswer;
            InitializeComponent();
            initializeTimer();
            initializeServerListener();

            Communicator.Send(Communicator.RequestType.GetQuestionRequest, "");
            GetQuestionResponse response = JsonConvert.DeserializeObject<GetQuestionResponse>(Communicator.Receive());
            initializeComponents(response);
        }

        private void listenToServer(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (serverListener.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                receiveMtx.WaitOne();
                if (!Communicator.IsDataAvailable())
                {
                    receiveMtx.ReleaseMutex();
                    continue;
                }
                MessageTypeResponse response = JsonConvert.DeserializeObject<MessageTypeResponse>(Communicator.Receive());
                receiveMtx.ReleaseMutex();

                CorrectAnswerResponse correctAnswerResponse = JsonConvert.DeserializeObject<CorrectAnswerResponse>(response.message);
                System.Threading.Thread.Sleep(25); //waiting to maybe receive another response

                if (response.type == MessageTypeResponse.Type.CorrectAnswerResponse)
                {
                    serverListener.ReportProgress((int)MessageTypeResponse.Type.CorrectAnswerResponse, correctAnswerResponse);
                    close(); return;
                }
                else if (response.type == MessageTypeResponse.Type.GetGameResultsResponse)
                {
                    serverListener.ReportProgress(3, correctAnswerResponse);

                    receiveMtx.WaitOne();
                    GetGameResultsResponse gameResultsResponse = JsonConvert.DeserializeObject<GetGameResultsResponse>(Communicator.Receive());
                    receiveMtx.ReleaseMutex();
                    serverListener.ReportProgress((int)MessageTypeResponse.Type.GetGameResultsResponse, gameResultsResponse);

                    close(); return;
                }
            }
        }

        private void close()
        {
            timer.Stop();
            serverListener.CancelAsync();
        }

        private void handleServerMessages(object sender, ProgressChangedEventArgs e)
        {
            switch ((MessageTypeResponse.Type)e.ProgressPercentage)
            {
                case MessageTypeResponse.Type.CorrectAnswerResponse:
                    markCorrectAnswer(((CorrectAnswerResponse)e.UserState).correctAnswer);

                    var timer = new DispatcherTimer { Interval = TimeSpan.FromSeconds(2.5) };
                    timer.Start();
                    timer.Tick += (sender, args) =>
                    {
                        timer.Stop();
                        ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage(timeToAnswer);
                    };
                    break;

                case MessageTypeResponse.Type.GetGameResultsResponse:
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new GameScorePage((GetGameResultsResponse)e.UserState);
                    break;

                case (MessageTypeResponse.Type)3:
                    markCorrectAnswer(((CorrectAnswerResponse)e.UserState).correctAnswer);
                    break;
            }
        }

        private void markCorrectAnswer(String correctAnswer)
        {
            //user didn't choose - all red
            if (this.selectedButtonIndex == 4)
            {
                foreach (ref Button button in this.buttons.AsSpan())
                {
                    button.Background = new BrushConverter().ConvertFrom("#eb8496") as SolidColorBrush;
                }
            }
            //user choose right - choice green
            else if (correctAnswer == this.buttons[this.selectedButtonIndex].Content.ToString())
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
            }

            //use choose wrong - choice red, right answer green
            else
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#eb8496") as SolidColorBrush;
                foreach (ref Button button in this.buttons.AsSpan())
                {
                    if (button.Content.ToString() == correctAnswer)
                    {
                        button.Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
                    }
                }
            }
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

        private void submitBTN_Click(object? sender, RoutedEventArgs? e)
        {
            String selectedAnswer = this.buttons[this.selectedButtonIndex].Content.ToString();

            SubmitAnswerRequest submitRequest;
            submitRequest.answer = selectedAnswer;
            submitRequest.timeToAnswer = ((float)answerTime.Elapsed.TotalSeconds);

            String jsonRepr = JsonConvert.SerializeObject(submitRequest);
            receiveMtx.WaitOne();
            Communicator.Send(Communicator.RequestType.SubmitAnswerRequest, jsonRepr);

            SubmitAnswerResponse submitResponse = JsonConvert.DeserializeObject<SubmitAnswerResponse>(Communicator.Receive());
            if (submitResponse.status == 0)
            {
                close();
                serverListener.RunWorkerAsync();
            }
            receiveMtx.ReleaseMutex();
        }
    }
}