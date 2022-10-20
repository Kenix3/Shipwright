#include "z_en_niw_lady.h"
#include "objects/object_ane/object_ane.h"
#include "objects/object_os_anime/object_os_anime.h"
#include "overlays/actors/ovl_En_Niw/z_en_niw.h"
#include "vt.h"
#include "soh/Enhancements/randomizer/adult_trade_shuffle.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_3 | ACTOR_FLAG_4)

void EnNiwLady_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNiwLady_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNiwLady_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80AB9F24(EnNiwLady* this, GlobalContext* globalCtx);
void EnNiwLady_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80ABA21C(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABAD38(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABA778(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABA878(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABA9B8(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABAB08(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABAC00(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABAA9C(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABAC84(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABA244(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABA654(EnNiwLady* this, GlobalContext* globalCtx);
void func_80ABAD7C(EnNiwLady* this, GlobalContext* globalCtx);

const ActorInit En_Niw_Lady_InitVars = {
    ACTOR_EN_NIW_LADY,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ANE,
    sizeof(EnNiwLady),
    (ActorFunc)EnNiwLady_Init,
    (ActorFunc)EnNiwLady_Destroy,
    (ActorFunc)EnNiwLady_Update,
    NULL,
    NULL,
};

static s16 sMissingCuccoTextIds[] = {
    0x5036, 0x5070, 0x5072, 0x5037, 0x5038, 0x5039, 0x503A, 0x503B, 0x503D, 0x503C,
};

static s16 D_80ABB3B4[] = {
    0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 10, 10, 0, { 0, 0, 0 } },
};

void EnNiwLady_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnNiwLady* this = (EnNiwLady*)thisx;

    this->objectAneIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_ANE);
    this->objectOsAnimeIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_OS_ANIME);
    if ((this->objectOsAnimeIndex < 0) || (this->objectAneIndex < 0)) {
        Actor_Kill(thisx);
        return;
    }
    this->unk_278 = 0;
    if (globalCtx->sceneNum == SCENE_LABO) {
        this->unk_278 = 1;
    }
    if ((this->unk_278 != 0) && IS_DAY) {
        Actor_Kill(thisx);
        return;
    }
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ ねぇちゃんうっふん ☆☆☆☆☆ %d\n" VT_RST, this->unk_278);
    osSyncPrintf("\n\n");
    this->actionFunc = func_80AB9F24;
    thisx->uncullZoneForward = 600.0f;
    this->getItemEntry = (GetItemEntry)GET_ITEM_NONE;
}

void EnNiwLady_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNiwLady* this = (EnNiwLady*)thisx;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnNiwLady_ChoseAnimation(EnNiwLady* this, GlobalContext* globalCtx, s32 arg2) {
    f32 frames;

    if (Text_GetFaceReaction(globalCtx, 8) != 0) {
        arg2 = 8;
    }
    if (arg2 != this->unk_270) {
        this->unk_275 = 0;
        this->unk_276 = 1;
        this->unk_270 = arg2;
        switch (arg2) {
            case 10:
                this->unk_275 = 1;
            case 9:
                frames = Animation_GetLastFrame(&gObjOsAnim_07D0);
                Animation_Change(&this->skelAnime, &gObjOsAnim_07D0, 1.0f, 0.0f, frames, ANIMMODE_LOOP, -10.0f);
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 8:
            case 21:
            case 22:
            case 24:
            case 29:
                frames = Animation_GetLastFrame(&gObjOsAnim_9F94);
                Animation_Change(&this->skelAnime, &gObjOsAnim_9F94, 1.0f, 0.0f, frames, ANIMMODE_LOOP, -10.0f);
                break;
            case 7:
            case 20:
            case 23:
            case 25:
            case 26:
            case 27:
            case 28:
                frames = Animation_GetLastFrame(&gObjOsAnim_0718);
                Animation_Change(&this->skelAnime, &gObjOsAnim_0718, 1.0f, 0.0f, frames, ANIMMODE_LOOP, -10.0f);
                break;
            case 100:
                frames = Animation_GetLastFrame(&gObjOsAnim_A630);
                Animation_Change(&this->skelAnime, &gObjOsAnim_A630, 1.0f, 0.0f, frames, ANIMMODE_LOOP, -10.0f);
                this->unk_276 = 0;
                break;
        }
        return;
    }
}

void func_80AB9F24(EnNiwLady* this, GlobalContext* globalCtx) {
    f32 frames;
    s32 pad;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->objectAneIndex) &&
        Object_IsLoaded(&globalCtx->objectCtx, this->objectOsAnimeIndex)) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->objectAneIndex].segment);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gCuccoLadySkel, NULL, this->jointTable, this->morphTable, 16);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->objectOsAnimeIndex].segment);
        this->unk_27E = 1;
        this->actor.gravity = -3.0f;
        Actor_SetScale(&this->actor, 0.01f);
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        this->unk_272 = 0;
        this->actor.targetMode = 6;
        this->actor.draw = EnNiwLady_Draw;
        switch (this->unk_278) {
            case 0:
                if (!(gSaveContext.itemGetInf[0] & 0x1000) && !LINK_IS_ADULT) {
                    frames = Animation_GetLastFrame(&gObjOsAnim_A630);
                    Animation_Change(&this->skelAnime, &gObjOsAnim_A630, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP, 0.0f);
                } else {
                    frames = Animation_GetLastFrame(&gObjOsAnim_07D0);
                    Animation_Change(&this->skelAnime, &gObjOsAnim_07D0, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP, 0.0f);
                }
                if (LINK_IS_ADULT) {
                    this->actionFunc = func_80ABA778;
                } else {
                    this->actionFunc = func_80ABA21C;
                }
                return;
            case 1:
                frames = Animation_GetLastFrame(&gObjOsAnim_07D0);
                Animation_Change(&this->skelAnime, &gObjOsAnim_07D0, 1.0f, 0.0f, (s16)frames, ANIMMODE_LOOP, 0.0f);
                this->actionFunc = func_80ABAD38;
                return;
        }
    }
}

void func_80ABA21C(EnNiwLady* this, GlobalContext* globalCtx) {
    this->actor.textId = sMissingCuccoTextIds[0];
    this->unk_262 = TEXT_STATE_DONE;
    this->actionFunc = func_80ABA244;
}

void func_80ABA244(EnNiwLady* this, GlobalContext* globalCtx) {
    EnNiw* currentCucco;
    s32 phi_s1;

    this->cuccosInPen = gSaveContext.n64ddFlag ? (7 - Randomizer_GetSettingValue(RSK_CUCCO_COUNT)) : 0;
    currentCucco = (EnNiw*)globalCtx->actorCtx.actorLists[ACTORCAT_PROP].head;
    while (currentCucco != NULL) {
        if (currentCucco->actor.id == ACTOR_EN_NIW) {
            if ((fabsf(currentCucco->actor.world.pos.x - 330.0f) < 90.0f) &&
                (fabsf(currentCucco->actor.world.pos.z - 1610.0f) < 190.0f)) {
                if (this->unk_26C == 0) {
                    gSaveContext.infTable[25] |= D_80ABB3B4[currentCucco->unk_2AA];
                    if (BREG(1) != 0) {
                        // "GET inside the chicken fence!"
                        osSyncPrintf(VT_FGCOL(GREEN) "☆ 鶏柵内ＧＥＴ！☆ %x\n" VT_RST,
                                     D_80ABB3B4[currentCucco->unk_2AA]);
                    }
                }
                this->cuccosInPen++;
            } else if (this->unk_26C == 0) {
                gSaveContext.infTable[25] &= ~D_80ABB3B4[currentCucco->unk_2AA];
            }
        }
        currentCucco = (EnNiw*)currentCucco->actor.next;
    }
    if (BREG(7) != 0) {
        this->cuccosInPen = BREG(7) - 1;
    }
    phi_s1 = this->cuccosInPen;
    if ((Message_GetState(&globalCtx->msgCtx) == TEXT_STATE_NONE) ||
        (Message_GetState(&globalCtx->msgCtx) == TEXT_STATE_DONE)) {
        this->unk_26E = 101;
    }
    if (this->cuccosInPen >= 7) {
        phi_s1 = 8;
        if ((this->unk_26C < 2) && (this->unk_26C == 0)) {
            phi_s1 = 7;
        }
    }
    if ((this->unk_26C != 0) && (phi_s1 < 7)) {
        phi_s1 = 9;
    }
    this->actor.textId = sMissingCuccoTextIds[phi_s1];
    if (Text_GetFaceReaction(globalCtx, 8) != 0) {
        this->actor.textId = Text_GetFaceReaction(globalCtx, 8);
        this->unk_262 = TEXT_STATE_DONE;
    }
    if ((this->unk_26C != 0) && (phi_s1 != 9)) {
        phi_s1 = 10;
        this->unk_26E = 11;
    }
    if (Actor_ProcessTalkRequest(&this->actor, globalCtx)) {
        osSyncPrintf("\n\n");
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ ねぇちゃん選択\t ☆☆☆☆ %d\n" VT_RST, phi_s1);
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ ねぇちゃんハート     ☆☆☆☆ %d\n" VT_RST, this->unk_26C);
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ ねぇちゃん保存       ☆☆☆☆ %d\n" VT_RST, this->unk_26A);
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ ねぇちゃん今\t ☆☆☆☆ %d\n" VT_RST, this->cuccosInPen);
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ this->actor.talk_message ☆☆ %x\n" VT_RST, this->actor.textId);
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ this->message_end_code   ☆☆ %d\n" VT_RST, this->unk_262);
        osSyncPrintf("\n\n");
        if (Text_GetFaceReaction(globalCtx, 8) == 0) {
            if (this->actor.textId == 0x503C) {
                func_80078884(NA_SE_SY_ERROR);
                this->unk_26C = 2;
                this->unk_262 = TEXT_STATE_EVENT;
                this->actionFunc = func_80ABA654;
                return;
            }
            this->unk_26E = phi_s1 + 1;
            if (phi_s1 == 7) {
                func_80078884(NA_SE_SY_TRE_BOX_APPEAR);
                this->unk_26C = 1;
                this->unk_262 = TEXT_STATE_EVENT;
                this->unk_26A = this->cuccosInPen;
                osSyncPrintf(VT_FGCOL(CYAN) "☆☆☆☆☆ 柵内BIT変更前 ☆☆ %x\n" VT_RST, gSaveContext.infTable[25]);
                gSaveContext.infTable[25] &= 0x1FF;
                osSyncPrintf(VT_FGCOL(CYAN) "☆☆☆☆☆ 柵内BIT変更後 ☆☆ %x\n" VT_RST, gSaveContext.infTable[25]);
                osSyncPrintf("\n\n");
                this->actionFunc = func_80ABA654;
                return;
            }
            if (this->unk_26A != this->cuccosInPen) {
                if (this->cuccosInPen < this->unk_26A) {
                    func_80078884(NA_SE_SY_ERROR);
                } else if (phi_s1 + 1 < 9) {
                    func_80078884(NA_SE_SY_TRE_BOX_APPEAR);
                }
            }
            if (this->unk_26A < this->cuccosInPen) {
                this->unk_26A = this->cuccosInPen;
                return;
            }
        }
    } else {
        func_8002F2CC(&this->actor, globalCtx, 100.0f);
    }
}

void func_80ABA654(EnNiwLady* this, GlobalContext* globalCtx) {
    if (this->unk_262 == Message_GetState(&globalCtx->msgCtx) && Message_ShouldAdvance(globalCtx)) {
        Message_CloseTextbox(globalCtx);
        osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ ハート ☆☆☆☆☆ %d\n" VT_RST, this->unk_26C);
        osSyncPrintf(VT_FGCOL(YELLOW) "☆☆☆☆☆ 爆弾   ☆☆☆☆☆ %d\n" VT_RST, this->unk_272);
        osSyncPrintf("\n\n");
        this->unk_26E = 0xB;
        if (!(gSaveContext.itemGetInf[0] & 0x1000)) {
            this->actor.parent = NULL;

            if (!gSaveContext.n64ddFlag) {
                this->getItemId = GI_BOTTLE;
                func_8002F434(&this->actor, globalCtx, GI_BOTTLE, 100.0f, 50.0f);
            } else {
                this->getItemEntry = Randomizer_GetItemFromKnownCheck(RC_KAK_ANJU_AS_CHILD, GI_BOTTLE);
                GiveItemEntryFromActor(&this->actor, globalCtx, this->getItemEntry, 100.0f, 50.0f);
            }

            this->actionFunc = func_80ABAC00;
            return;
        }
        if (this->unk_26C == 1) {
            this->getItemId = GI_RUPEE_PURPLE;
            func_8002F434(&this->actor, globalCtx, GI_RUPEE_PURPLE, 100.0f, 50.0f);
            this->actionFunc = func_80ABAC00;
        }
        this->actionFunc = func_80ABA244;
    }
}

static s16 sTradeItemTextIds[] = { 0x503E, 0x503F, 0x5047, 0x5040, 0x5042, 0x5043,
                                   0x5044, 0x00CF, 0x5045, 0x5042, 0x5027 };

void func_80ABA778(EnNiwLady* this, GlobalContext* globalCtx) {
    // "☆☆☆☆☆ Adult message check ☆☆☆☆☆"
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ アダルトメッセージチェック ☆☆☆☆☆ \n" VT_RST);
    this->unk_262 = TEXT_STATE_DONE;
    this->unk_273 = 0;
    if (!(gSaveContext.itemGetInf[2] & 0x1000)) {
        if (this->unk_274 != 0) {
            this->unk_27A = 1;
        } else {
            this->unk_27A = 0;
        }
        this->unk_273 = 1;
        this->unk_262 = TEXT_STATE_CHOICE;
    } else {
        this->unk_27A = 2;
        if (!(gSaveContext.itemGetInf[2] & 0x4000)) {
            this->unk_27A = 3;
            if (gSaveContext.eventChkInf[6] & 0x400) {
                this->unk_27A = 9;
                if (this->unk_277 != 0) {
                    this->unk_27A = 10;
                }
            } else {
                this->unk_27A = 4;
            }
        }
    }
    this->actor.textId = sTradeItemTextIds[this->unk_27A];
    this->actionFunc = func_80ABA878;
}

void func_80ABA878(EnNiwLady* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s8 playerExchangeItemId;

    if ((Message_GetState(&globalCtx->msgCtx) == TEXT_STATE_NONE) ||
        (Message_GetState(&globalCtx->msgCtx) == TEXT_STATE_DONE)) {
        this->unk_26E = 11;
    }
    if (Actor_ProcessTalkRequest(&this->actor, globalCtx)) {
        playerExchangeItemId = func_8002F368(globalCtx);
        if ((playerExchangeItemId == 6) && (gSaveContext.eventChkInf[6] & 0x400)) {
            func_80078884(NA_SE_SY_TRE_BOX_APPEAR);
            player->actor.textId = sTradeItemTextIds[5];
            this->unk_26E = this->unk_27A + 21;
            this->unk_262 = TEXT_STATE_CHOICE;
            this->actionFunc = func_80ABAB08;
        } else if (playerExchangeItemId != 0) {
            player->actor.textId = sTradeItemTextIds[7];
            this->unk_26E = this->unk_27A + 21;
        } else {
            this->unk_274 = 1;
            this->unk_26E = this->unk_27A + 21;
            this->actionFunc = !this->unk_273 ? func_80ABA778 : func_80ABA9B8;
        }
    } else {
        func_8002F298(&this->actor, globalCtx, 50.0f, 6);
    }
}

void func_80ABA9B8(EnNiwLady* this, GlobalContext* globalCtx) {
    if ((this->unk_262 == Message_GetState(&globalCtx->msgCtx)) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                Message_CloseTextbox(globalCtx);
                this->actor.parent = NULL;

                if (!gSaveContext.n64ddFlag) {
                    func_8002F434(&this->actor, globalCtx, GI_POCKET_EGG, 200.0f, 100.0f);
                } else {
                    // TODO: get-item-rework Adult trade sequence
                    this->getItemEntry = Randomizer_GetItemFromKnownCheck(RC_KAK_ANJU_AS_ADULT, GI_POCKET_EGG);
                    gSaveContext.itemGetInf[2] |= 0x1000;
                }

                this->actionFunc = func_80ABAC00;
                break;
            case 1:
                this->actor.textId = sTradeItemTextIds[3];
                this->unk_26E = this->unk_27A + 21;
                Message_ContinueTextbox(globalCtx, this->actor.textId);
                this->unk_262 = TEXT_STATE_EVENT;
                this->actionFunc = func_80ABAA9C;
                break;
        }
    }
}

void func_80ABAA9C(EnNiwLady* this, GlobalContext* globalCtx) {
    this->unk_26E = 11;
    if ((this->unk_262 == Message_GetState(&globalCtx->msgCtx)) && Message_ShouldAdvance(globalCtx)) {
        Message_CloseTextbox(globalCtx);
        this->actionFunc = func_80ABA778;
    }
}

void func_80ABAB08(EnNiwLady* this, GlobalContext* globalCtx) {
    if ((this->unk_262 == Message_GetState(&globalCtx->msgCtx)) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                Message_CloseTextbox(globalCtx);
                this->actor.parent = NULL;
                if (!gSaveContext.n64ddFlag) {
                    func_8002F434(&this->actor, globalCtx, GI_COJIRO, 200.0f, 100.0f);
                } else {
                    // TODO: get-item-rework Adult trade sequence
                    this->getItemEntry = Randomizer_GetItemFromKnownCheck(RC_KAK_TRADE_POCKET_CUCCO, GI_COJIRO);
                    Randomizer_ConsumeAdultTradeItem(globalCtx, ITEM_POCKET_CUCCO);
                    gSaveContext.itemGetInf[2] |= 0x4000;
                }
                this->actionFunc = func_80ABAC00;
                break;
            case 1:
                Message_CloseTextbox(globalCtx);
                this->unk_277 = 1;
                this->actor.textId = sTradeItemTextIds[8];
                this->unk_26E = this->unk_27A + 21;
                Message_ContinueTextbox(globalCtx, this->actor.textId);
                this->unk_262 = TEXT_STATE_EVENT;
                this->actionFunc = func_80ABAA9C;
                break;
        }
    }
}

void func_80ABAC00(EnNiwLady* this, GlobalContext* globalCtx) {
    s32 getItemId;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actionFunc = func_80ABAC84;
    } else {
        getItemId = this->getItemId;
        if (LINK_IS_ADULT) {
            if (!gSaveContext.n64ddFlag) {
                getItemId = !(gSaveContext.itemGetInf[2] & 0x1000) ? GI_POCKET_EGG : GI_COJIRO;
            } else {
                // TODO: get-item-rework Adult trade sequence
                getItemId = this->getItemEntry.getItemId;
                GiveItemEntryFromActor(&this->actor, globalCtx, this->getItemEntry, 200.0f, 100.0f);
                // Skip setting item flags because that was done earlier
                this->actionFunc = func_80ABA778;
            }
        }
        if (this->getItemEntry.getItemId == GI_NONE) {
            func_8002F434(&this->actor, globalCtx, getItemId, 200.0f, 100.0f);
        }
    }
}

void func_80ABAC84(EnNiwLady* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) != TEXT_STATE_DONE) || !Message_ShouldAdvance(globalCtx)) {
        return;
    }
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 正常終了 ☆☆☆☆☆ \n" VT_RST);
    if (LINK_IS_ADULT) {
        if (!(gSaveContext.itemGetInf[2] & 0x1000)) {
            gSaveContext.itemGetInf[2] |= 0x1000;
        } else {
            gSaveContext.itemGetInf[2] |= 0x4000;
        }
        this->actionFunc = func_80ABA778;
    } else {
        gSaveContext.itemGetInf[0] |= 0x1000;
        this->unk_262 = TEXT_STATE_DONE;
        this->actionFunc = func_80ABA244;
    }
}

void func_80ABAD38(EnNiwLady* this, GlobalContext* globalCtx) {
    osSyncPrintf(VT_FGCOL(GREEN) "☆☆☆☆☆ 通常メッセージチェック ☆☆☆☆☆ \n" VT_RST);
    this->unk_262 = TEXT_STATE_DONE;
    this->actionFunc = func_80ABAD7C;
}

void func_80ABAD7C(EnNiwLady* this, GlobalContext* globalCtx) {
    this->actor.textId = 0x503D;
    if (Text_GetFaceReaction(globalCtx, 8) != 0) {
        this->actor.textId = Text_GetFaceReaction(globalCtx, 8);
    }
    if ((Message_GetState(&globalCtx->msgCtx) == TEXT_STATE_NONE) ||
        (Message_GetState(&globalCtx->msgCtx) == TEXT_STATE_DONE)) {
        this->unk_26E = 8;
    }
    if (Actor_ProcessTalkRequest(&this->actor, globalCtx)) {
        this->unk_274 = 1;
        this->unk_26E = this->unk_27A + 9;
        this->actionFunc = func_80ABAD38;
    } else {
        func_8002F2CC(&this->actor, globalCtx, 100.0f);
    }
}

void EnNiwLady_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnNiwLady* this = (EnNiwLady*)thisx;
    Player* player = GET_PLAYER(globalCtx);

    Actor_SetFocus(thisx, 60.0f);
    this->unk_288.unk_18 = player->actor.world.pos;
    if (!LINK_IS_ADULT) {
        this->unk_288.unk_18.y = player->actor.world.pos.y - 10.0f;
    }
    func_80034A14(thisx, &this->unk_288, 2, 4);
    this->unk_254 = this->unk_288.unk_08;
    this->unk_25A = this->unk_288.unk_0E;
    if (this->unk_276 == 0) {
        Math_SmoothStepToS(&this->unk_254.y, 0, 5, 3000, 0);
    }
    gSegments[6] = VIRTUAL_TO_PHYSICAL(globalCtx->objectCtx.status[this->objectOsAnimeIndex].segment);
    if (this->objectOsAnimeIndex >= 0) {
        if (this->unk_27E != 0) {
            if (this->unk_26E != 0) {
                this->unk_26E--;
                EnNiwLady_ChoseAnimation(this, globalCtx, this->unk_26E);
                this->unk_26E = 0;
            }
            SkelAnime_Update(&this->skelAnime);
        }
        this->objectAneIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_ANE);
        if (this->objectAneIndex >= 0) {
            this->actionFunc(this, globalCtx);
            if (this->unusedTimer2 != 0) {
                this->unusedTimer2--;
            }
            if (this->unusedRandomTimer != 0) {
                this->unusedRandomTimer--;
            }
            this->unusedTimer++;
            if (this->unusedRandomTimer == 0) {
                this->faceState++;
                if (this->faceState >= 3) {
                    this->faceState = 0;
                    this->unusedRandomTimer = ((s16)Rand_ZeroFloat(60.0f) + 0x14);
                }
            }
            Actor_UpdateBgCheckInfo(globalCtx, thisx, 20.0f, 20.0f, 60.0f, 0x1D);
            Collider_UpdateCylinder(thisx, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

Gfx* func_80ABB0A0(GraphicsContext* gfxCtx) {
    Gfx* dList;

    dList = Graph_Alloc(gfxCtx, sizeof(Gfx));
    gSPEndDisplayList(dList);
    return dList;
}

s32 EnNiwLady_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               void* thisx) {
    EnNiwLady* this = (EnNiwLady*)thisx;
    s32 pad;

    if (limbIndex == 15) {
        rot->x += this->unk_254.y;
        rot->z += this->unk_254.x;
    }
    if (limbIndex == 8) {
        rot->x += this->unk_25A.y;
    }
    if (this->unk_275 != 0) {
        if ((limbIndex == 8) || (limbIndex == 10) || (limbIndex == 13)) {
            rot->y += (Math_SinS((globalCtx->state.frames * ((limbIndex * 0x32) + 0x814))) * 200.0f);
            rot->z += (Math_CosS((globalCtx->state.frames * ((limbIndex * 0x32) + 0x940))) * 200.0f);
        }
    }
    return false;
}

void EnNiwLady_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static void* sEyeTextures[] = { gCuccoLadyEyeOpenTex, gCuccoLadyEyeHalfTex, gCuccoLadyEyeClosedTex };
    EnNiwLady* this = (EnNiwLady*)thisx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (this->unk_27E != 0) {
        func_80093D18(globalCtx->state.gfxCtx);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
        gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sEyeTextures[this->faceState]));
        gSPSegment(POLY_OPA_DISP++, 0x0C, func_80ABB0A0(globalCtx->state.gfxCtx));
        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              this->skelAnime.dListCount, EnNiwLady_OverrideLimbDraw, NULL, this);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}