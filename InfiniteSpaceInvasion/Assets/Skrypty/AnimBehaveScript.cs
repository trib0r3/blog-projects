using UnityEngine;
using System.Collections;

public class AnimBehaveScript : MonoBehaviour {

	// Use this for initialization
	void Start () {
		Invoke("killMe",0.8f);
	}

	void killMe()
	{
		Destroy(gameObject);
	}
}
