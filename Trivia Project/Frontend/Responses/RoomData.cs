using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Responses
{
    internal struct RoomData
    {
		public int id;
		public string name;
		public int maxPlayers;
		public int numOfQuestionsInGame;
		public int timePerQuestion;
		public bool isActive;
	}
}
