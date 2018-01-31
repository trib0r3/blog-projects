using UnityEngine;

public class BlockController : MonoBehaviour
{
	SpriteRenderer rend;

	void Awake()
	{
		rend = GetComponent<SpriteRenderer>();
	}

	void Start()
	{
		float r = Random.Range(0f, 1f);
		float g = Random.Range(0f, 1f);
		float b = Random.Range(0f, 1f);

		rend.color = new Color(r, g, b);
	}


	void OnCollisionExit2D()
	{
		Destroy(gameObject, 0.1f);
	}
}
