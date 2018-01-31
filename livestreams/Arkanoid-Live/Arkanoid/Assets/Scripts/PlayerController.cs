using UnityEngine;

public class PlayerController : MonoBehaviour
{
	public float speed = 5f;
	private Rigidbody2D rb;

	void Awake()
	{
		rb = GetComponent<Rigidbody2D>();
	}


	void Update ()
	{
		float dir = Input.GetAxis("Horizontal");

		if (dir < 0)
		{
			dir = -1;
		}
		else if(dir > 0)
		{
			dir = 1;
		}

		rb.velocity = new Vector2(dir * speed, 0) * Time.deltaTime;
	}


}
