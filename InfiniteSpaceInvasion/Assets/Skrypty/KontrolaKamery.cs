using UnityEngine;
using System.Collections;

public class KontrolaKamery : MonoBehaviour {

	public Transform gracz;
	void Update () {
		if(gracz == null)
		{
			Invoke("endGame",1);
			GameObject.Find("_GM").SendMessage("stopCounting");

		}
		else
		{
			transform.position = new Vector3(gracz.position.x+6.5f,0,-20);
		}
	}

	void endGame()
	{
		Application.LoadLevel(2);
	}
}
