using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenSource.WebRTC;

namespace WebRTC_Sample
{
    public static class FormExtensions
    {
        public static WebRTCCommons.CustomAwaiter<bool> ContextSwitchToMessagePumpAsync(this System.Windows.Forms.Form f)
        {
            WebRTCCommons.CustomAwaiter<bool> retVal = new WebRTCCommons.CustomAwaiter<bool>();
            retVal.forceWait();
            try
            {
                f.BeginInvoke((Action<WebRTCCommons.CustomAwaiter<bool>>)((a) =>
                {
                    a.SetComplete(true);
                }), retVal);
            }
            catch
            {
            }
            return (retVal);
        }
    }
}
