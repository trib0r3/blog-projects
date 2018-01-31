using UnityEngine;
using System.Collections;

public class ZombieAI : MonoBehaviour {

	public Transform target;
	public float speed = 20;

	public GameObject AnimOnTouch;

	void Update () 
	{
		GameObject g = GameObject.Find("Gracz");
		if(g == null)
			return;

		target = g.transform;

		float angle = 0;
		
		Vector3 relative = transform.InverseTransformPoint(target.position);
		angle = Mathf.Atan2(relative.x, relative.y)*Mathf.Rad2Deg;
		transform.Rotate(0,0, -angle);

		rigidbody2D.AddForce(gameObject.transform.up * 0.5f * speed);
	}

	void OnCollisionEnter2D(Collision2D coll)
	{
		if(coll.gameObject.tag == "Gracz")
		{
			if(GameObject.FindGameObjectWithTag("GM").GetComponent<GameMaster>().zycia > 0)
			{
				GameObject.FindGameObjectWithTag("GM").GetComponent<GameMaster>().zycia--;
				Instantiate(AnimOnTouch,coll.transform.position,coll.transform.rotation);
				Destroy(this.gameObject);
				return;
			}

			Destroy(coll.gameObject);
			Destroy(this.gameObject);

			Instantiate(AnimOnTouch,transform.position,transform.rotation);
		}
	}

	void OnDisable()
	{
		if(this.gameObject.tag == "Sniper")
		{
			GameObject g = GameObject.FindWithTag("GM");
			if(g != null)
			{
				g.GetComponent <GameMaster>().ammunition+=10;
			}
		}
	}
}
