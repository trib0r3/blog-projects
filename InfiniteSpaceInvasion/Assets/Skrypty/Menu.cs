using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Menu : MonoBehaviour {


	public Slider slider;				// slider poziomu trudnosci
	public Toggle m;					// przycisk czy muzyka
	public Toggle s;					// czy dźwięki

	public GameObject credits;			// panel credits


	int muzyka = 1;						// 1 wlaczona, 0 wylaczona
	int dzwieki = 1;					// jak wyżej


	public void exit()
	{
		Application.Quit();
	}

	public void rozpocznij()
	{
		PlayerPrefs.SetInt("trudnosc",(int)slider.value);

		muzyka = (m.isOn ? 1 : 0);
		dzwieki = (s.isOn ? 1 : 0);

		PlayerPrefs.SetInt("muzyka",muzyka);
		PlayerPrefs.SetInt("dzwiek",dzwieki);

		Application.LoadLevel(1);
	}


	public void idzDo(string adres)
	{
		Application.OpenURL(adres);
	}


	public void wlacznik()
	{
		credits.SetActive(!credits.activeSelf);
	}
}
