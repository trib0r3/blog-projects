using UnityEngine;
using System.Collections;

public class GameMaster : MonoBehaviour {

	public GUISkin skin;				// skin (czcionka, itd)
	public SpriteRenderer tlo;			// tlo do zmiany koloru

	public float zycia;					// ilosc uderzen jakie moze zniesc statek

	public int ammunition;				// ilosc amunicji gracza (punkty)
	public int poziomTrudnosci;			// poziom trudnosci: 1,2,3


	float dystans = 0;					// przebyty dystans przez gracza
	bool odliczanie = true;				// czy jeszcze ma byc liczony dystans

	float CzasDoZmianyTla;				// czas po którym zostanie zmieniony kolor tla
	Vector3 deltaColor;					// Vector o jaki mają zmieniać się kolory co klatkę
	bool zmienienieKoloru = false;		// czy rozpoczęto zmienianie koloru

	int muzyka;							// czy odwarzac muzyke (1 true, 0 false)
	public int dzwiek;					// czy odtwarzać dźwięk

	int wszystkieZycia;

	void Awake()
	{
		audio.volume = 0.2f;
	}

	void Start () {
		poziomTrudnosci = PlayerPrefs.GetInt("trudnosc",1);
		muzyka = PlayerPrefs.GetInt("muzyka",1);
		dzwiek = PlayerPrefs.GetInt("dzwiek",1);

		if(muzyka == 0)
			audio.mute = true;

		audio.volume = 1;

		switch(poziomTrudnosci)
		{
		case 1:
			ammunition = 1000;
			zycia = 10;
			wszystkieZycia = 10;
			break;
		case 2:
			ammunition = 500;
			zycia = 5;
			wszystkieZycia = 5;
			break;
		case 3:
			ammunition = 100;
			zycia = 3;
			wszystkieZycia = 3;
			break;
		}


		CzasDoZmianyTla = Random.Range(5f,20f);
	}


	void OnGUI()
	{
		if(odliczanie)
			dystans +=  Time.deltaTime;

		GUI.skin = skin;
		GUI.Label(new Rect(20,20,200,100),"Score: " + (int)(dystans * 10));
		GUI.Label(new Rect(20,50,200,100),"Ammunition: " + ammunition);
		GUI.Label(new Rect(20,80,200,100),"Shields: " + (int)(zycia/wszystkieZycia * 100) + "%");
	}


	void stopCounting()
	{
		odliczanie = false;	
	}


	void OnDisable()
	{
		PlayerPrefs.SetInt("Dystans",(int)(dystans * 10));
	}


	void Update()
	{
		if(Input.GetKeyDown(KeyCode.Escape))
		{
			Application.LoadLevel(0);
		}

		if(Time.time >= CzasDoZmianyTla)
		{
			if(!zmienienieKoloru)
			{
				deltaColor = new Vector3(Random.Range(-0.05f,0.05f),Random.Range(-0.05f,0.05f),Random.Range(-0.05f,0.05f));

				zmienienieKoloru = true;
			}
			if(zmienienieKoloru)
			{
				tlo.color = new Color(tlo.color.r+deltaColor.x,tlo.color.g+deltaColor.y,tlo.color.b+deltaColor.z);
				if(tlo.color.r >= 255 || tlo.color.r <= 0)
					deltaColor.x *= 0;

				if(tlo.color.g >= 255 || tlo.color.g <= 0)
					deltaColor.y *= 0;

				if(tlo.color.b >= 255 || tlo.color.b <= 0)
					deltaColor.z *= 0;
			}

			if(Time.time > CzasDoZmianyTla + 1)
			{
				zmienienieKoloru = false;
				CzasDoZmianyTla = Time.time + Random.Range(7,15);
				//Debug.Log("Ustaliłem nowy czas!");
			}
		}
	}
}