using UnityEngine;
using System.Collections;

public class Destroyer : MonoBehaviour {
	

	void OnTriggerEnter2D(Collider2D other)
	{
		if(other.tag == "Gracz")
		{
			Debug.Log("Wykrto gracza!");
			Debug.Break();
			return;
		}

		//if(other.tag == "MainCamera" || other.gameObject.transform.parent.tag == "MainCamera")
			//return;

		if(other.gameObject.transform.parent)
		{
			Destroy(other.gameObject.transform.parent.gameObject);
		}
		else
		{
			Destroy(other.gameObject);
		}
	}


}
