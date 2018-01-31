using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GameOverScript : MonoBehaviour {

	public Text tekst;

	void Start()
	{
		tekst.text = "Your score: " + PlayerPrefs.GetInt("Dystans");
	}

	void retry()
	{
		Application.LoadLevel(1);
	}

	void menu()
	{
		Application.LoadLevel(0);
	}

	void exit()
	{
		Application.Quit();
	}
}
