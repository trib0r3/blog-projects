using UnityEngine;
using System.Collections;

public class Spawn : MonoBehaviour {

	public GameObject ObjectToSpawn;		// obiekt do zespawnowania
	public float TimeToStart = 0;			// czas po którym może zostać zespawnowana PIERWSZA jednostka

	public float timeMin = 1f;				// czas minimalny od ostatniego spawnu po którym zostanie stworzona kolejna jednostka
	public float timeMax = 4f;				// czas maksymalny po jakim zostanie utworzona nowa jednostka
	
	int iloscStatkow=0;						// ilość zespawnowanych statków przez dany spawn


	void Start () 
	{
		Invoke("spawn",TimeToStart+Random.Range(0,0.9f));
	}
	
	void spawn()
	{
		Instantiate(ObjectToSpawn,transform.position,Quaternion.identity);
		iloscStatkow++;

		if(iloscStatkow % 10 == 0 && timeMax > timeMin + 0.07f)
		{
			timeMax -= 0.05f;
		}

		Invoke("spawn",Random.Range(timeMin,timeMax));
	}
}
