﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Responses
{
    internal struct UpdateResponse
    {
        public enum Type
        {
            StartGame,
            LeaveRoom
        };
        public int status;
        public int type;
    }
}
