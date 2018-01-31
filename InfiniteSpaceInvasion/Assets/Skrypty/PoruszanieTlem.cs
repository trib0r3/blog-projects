using UnityEngine;
using System.Collections;

public class PoruszanieTlem : MonoBehaviour {

	float x;
	float prevX;

	public GameObject sprite;
	public GameObject sprite2;

	void Start()
	{

		x = Input.mousePosition.x;
		prevX = x;
	}
	
	void Update () {
		x = Input.mousePosition.x;

		if(x > prevX)
		{
			sprite.transform.position = new Vector3(sprite.transform.position.x - 0.009f,0,0);
			sprite2.transform.position = new Vector3(sprite2.transform.position.x + 0.005f,0,0);
		}
		else if(x < prevX)
		{
			sprite.transform.position = new Vector3(sprite.transform.position.x + 0.009f,0,0);
			sprite2.transform.position = new Vector3(sprite2.transform.position.x - 0.005f,0,0);
		}

		prevX = x;
	}
}
