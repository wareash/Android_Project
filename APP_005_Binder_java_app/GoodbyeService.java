/* impl goodbye service */

import android.util.Slog;

public class GoodbyeService extends IGoodbyeService.Stub
{
	private static final String TAG = "GoodbyeService";
	private int cnt1 = 0;
	private int cnt2 = 0;

	public void saygoodbye() throws android.os.RemoteException{
		cnt1++;
		Slog.i(TAG, "Say goodbye cnt = "+cnt1);
	}
	public int saygoodbye_to(java.lang.String name) throws android.os.RemoteException{
		cnt2++;
		Slog.i(TAG, "Say goodbye to "+name+ "cnt ="+cnt2);
		return cnt2;
	}
}
