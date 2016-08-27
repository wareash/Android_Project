/* impl hello service */

import android.util.Slog;

public class HelloService extends IHelloService.Stub
{
	private static final String TAG = "HelloService";
	private int cnt1 = 0;
	private int cnt2 = 0;

	public void sayhello() throws android.os.RemoteException{
		cnt1++;
		Slog.i(TAG, "Say Hello cnt = "+cnt1);
	}
	public int sayhello_to(java.lang.String name) throws android.os.RemoteException{
		cnt2++;
		Slog.i(TAG, "Say Hello to "+name+ "cnt ="+cnt2);
		return cnt2;
	}
}
