#include "stdafx.h"
#include "Blue.h"
#include "Player.h"
//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "collision/CollisionObject.h"

Blue::Blue()
{
	characterController.Init(30.0f, 5.0f, position);
	//���f����ǂݍ���
	modelRender.Init("Assets/modelData/Blue.tkm");
	//�v���C���[�̃I�u�W�F�N�g�����������Ă���
	player = FindGO<Player>("player");
	//SetScale�͑傫����ς���
	modelRender.SetScale(3.0f,3.0f,3.0f);

	//�v���C���[���쐬�����A���o�[�p�̃R���W�����̔z����擾�B
const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_Blue");

	//for���Ŕz����񂷁B
	for (auto collision : collisions)
	{
		//���o�[���g�̃R���W�����ƃv���C���[�̃R���W�������B
	//�Փ˂��Ă�����B
		if (collision->IsHit(collisionObject) == true)
		{
			//�����X�e�[�g�ɑJ�ڂ�����B
			m_BlueState = enBlueState_Push;

			//���ʉ��𗬂��B
			/*SoundSource* se = NewGO<SoundSource>(0);
			se->Init(6);
			se->Play(false);
			se->SetVolume(0.6f);*/
		}
	}
	
	CollisionObject* collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = position;
	//����̃R���W�������쐬����B
	collisionObject->CreateSphere(collisionPosition, //���W�B
		Quaternion::Identity, //��]�B
		30.0f); //���̑傫��(���a)�B
	collisionObject->SetName("player_Blue");

	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	
	
}

Blue::~Blue()
{
	//�R���W�����I�u�W�F�N�g���폜����
	DeleteGO(collisionObject);
}


void Blue::ProcessTransitionPullState()
{
	//�v���C���[���쐬�����A���o�[�p�̃R���W�����̔z����擾�B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_Blue");

	//for���Ŕz����񂷁B
	for (auto collision : collisions)
	{
		//���o�[���g�̃R���W�����ƃv���C���[�̃R���W�������B
	//�Փ˂��Ă�����B
		if (collision->IsHit(collisionObject) == true)
		{
			//�����X�e�[�g�ɑJ�ڂ�����B
			m_BlueState = enBlueState_Pull;

			//���ʉ��𗬂��B
			/*SoundSource* se = NewGO<SoundSource>(0);
			se->Init(6);
			se->Play(false);
			se->SetVolume(0.6f);*/
		}
	}
}


void Blue::Update()
{
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	m_moveSpeed.x = 5.0f;
	m_moveSpeed.z = 5.0f;


	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y�����ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	/*forward.x = 0.0f;
	right.x = 0.0f;*/

	right *= stickL.x * 30.0f;
	forward *= stickL.y * 30.0f;

	moveSpeed += right + forward;


	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (hata == false) {
			hata = true;
		}
		else if(hata == true){
			{
				hata = false;
			}
		}
	}
	if (hata == true) {


		if (stickL.x != 0.0f || stickL.y != 0.0f) {
			QueRot.x = stickL.x;
			QueRot.z = stickL.y;
		}

		QueRot.Normalize();

		position.x += QueRot.x * m_moveSpeed.x;
		position.y += QueRot.y * m_moveSpeed.y;
		position.z += QueRot.z * m_moveSpeed.z;

		//��]�����Z����
		rot.AddRotationDegY(0.0f);
		//�G�`������ɉ�]��������
		modelRender.SetRotation(rot);

		//�G�`������ɍ��W��������
		modelRender.SetPosition(position);
		//�G�`������̍X�V����
		modelRender.Update();

		position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

		//moveSpeed += right + forward;

		//m_modelRender.SetPosition(position);
		/*colli = NewGO<CollisionObject>(0);

		colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 50.0f);

		colli->SetName("Blue");

		colli->SetPosition(position);*/

		//�R���W�����I�u�W�F�N�g�쐬
		

		//���O��t����B
		//collisionObject->SetName("Player_Object");

		
	}
	

}

void Blue::Render(RenderContext& renderContext)
{
	//�G��`�悷��
	modelRender.Draw(renderContext);
}