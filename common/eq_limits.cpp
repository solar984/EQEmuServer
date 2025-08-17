/*	EQEMu: Everquest Server Emulator

	Copyright (C) 2001-2016 EQEMu Development Team (http://eqemulator.net)

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; version 2 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY except by those people which sell it, which
	are required to give you total support for your newly bought product;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "emu_constants.h"
#include "emu_limits.h"
#include "rulesys.h"

#include <memory>


static bool global_dictionary_init = false;
void EQ::InitializeDynamicLookups() {
	if (global_dictionary_init)
		return;

	constants::InitializeDynamicLookups();
	inventory::InitializeDynamicLookups();
	behavior::InitializeDynamicLookups();
	spells::InitializeDynamicLookups();

	global_dictionary_init = true;
}

static std::unique_ptr<EQ::constants::LookupEntry> constants_dynamic_nongm_lookup_entries[EQ::versions::ClientVersionCount];
static std::unique_ptr<EQ::constants::LookupEntry> constants_dynamic_gm_lookup_entries[EQ::versions::ClientVersionCount];
static const EQ::constants::LookupEntry constants_static_lookup_entries[EQ::versions::ClientVersionCount] =
{
	/*[ClientVersion::Unknown] =*/
	EQ::constants::LookupEntry(
		ClientUnknown::constants::EXPANSION,
		ClientUnknown::constants::EXPANSION_BIT,
		ClientUnknown::constants::EXPANSIONS_MASK,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL
	),
	/*[ClientVersion::Client62] =*/
	EQ::constants::LookupEntry(
		Client62::constants::EXPANSION,
		Client62::constants::EXPANSION_BIT,
		Client62::constants::EXPANSIONS_MASK,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL
	),
	/*[ClientVersion::Titanium] =*/
	EQ::constants::LookupEntry(
		Titanium::constants::EXPANSION,
		Titanium::constants::EXPANSION_BIT,
		Titanium::constants::EXPANSIONS_MASK,
		Titanium::constants::CHARACTER_CREATION_LIMIT,
		Titanium::constants::SAY_LINK_BODY_SIZE,
		Titanium::INULL
	),
	/*[ClientVersion::SoF] =*/
	EQ::constants::LookupEntry(
		SoF::constants::EXPANSION,
		SoF::constants::EXPANSION_BIT,
		SoF::constants::EXPANSIONS_MASK,
		SoF::constants::CHARACTER_CREATION_LIMIT,
		SoF::constants::SAY_LINK_BODY_SIZE,
		SoF::INULL
	),
	/*[ClientVersion::SoD] =*/
	EQ::constants::LookupEntry(
		SoD::constants::EXPANSION,
		SoD::constants::EXPANSION_BIT,
		SoD::constants::EXPANSIONS_MASK,
		SoD::constants::CHARACTER_CREATION_LIMIT,
		SoD::constants::SAY_LINK_BODY_SIZE,
		SoD::INULL
	)
};

static bool constants_dictionary_init = false;
void EQ::constants::InitializeDynamicLookups() {
	if (constants_dictionary_init == true)
		return;
	constants_dictionary_init = true;

	if (RuleB(World, UseClientBasedExpansionSettings))
		return;

	// use static references for now
}

const EQ::constants::LookupEntry* EQ::constants::DynamicLookup(versions::ClientVersion client_version, bool gm_flag)
{
	if (gm_flag)
		return DynamicGMLookup(client_version);
	else
		return DynamicNonGMLookup(client_version);
}

const EQ::constants::LookupEntry* EQ::constants::DynamicNonGMLookup(versions::ClientVersion client_version)
{
	client_version = versions::ValidateClientVersion(client_version);
	if (constants_dynamic_nongm_lookup_entries[static_cast<int>(client_version)])
		return constants_dynamic_nongm_lookup_entries[static_cast<int>(client_version)].get();

	return &constants_static_lookup_entries[static_cast<int>(client_version)];
}

const EQ::constants::LookupEntry* EQ::constants::DynamicGMLookup(versions::ClientVersion client_version)
{
	client_version = versions::ValidateClientVersion(client_version);
	if (constants_dynamic_gm_lookup_entries[static_cast<int>(client_version)])
		return constants_dynamic_gm_lookup_entries[static_cast<int>(client_version)].get();

	return &constants_static_lookup_entries[static_cast<int>(client_version)];
}

const EQ::constants::LookupEntry* EQ::constants::StaticLookup(versions::ClientVersion client_version)
{
	return &constants_static_lookup_entries[static_cast<int>(versions::ValidateClientVersion(client_version))];
}

static std::unique_ptr<EQ::inventory::LookupEntry> inventory_dynamic_nongm_lookup_entries[EQ::versions::MobVersionCount];
static std::unique_ptr<EQ::inventory::LookupEntry> inventory_dynamic_gm_lookup_entries[EQ::versions::MobVersionCount];
static const EQ::inventory::LookupEntry inventory_static_lookup_entries[EQ::versions::MobVersionCount] =
{
	/*[MobVersion::Unknown] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			ClientUnknown::INULL, ClientUnknown::INULL, ClientUnknown::INULL,
			ClientUnknown::INULL, ClientUnknown::INULL, ClientUnknown::INULL,
			ClientUnknown::INULL, ClientUnknown::INULL, ClientUnknown::INULL,
			ClientUnknown::INULL, ClientUnknown::INULL, ClientUnknown::INULL,
			ClientUnknown::INULL, ClientUnknown::INULL, ClientUnknown::INULL,
			ClientUnknown::INULL, ClientUnknown::INULL, ClientUnknown::INULL,
			ClientUnknown::INULL
		),

		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,

		false,
		false,
		false,
		false
	),
	/*[MobVersion::Client62] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			Client62::INULL, Client62::INULL, Client62::INULL,
			Client62::INULL, Client62::INULL, Client62::INULL,
			Client62::INULL, Client62::INULL, Client62::INULL,
			Client62::INULL, Client62::INULL, Client62::INULL,
			Client62::INULL, Client62::INULL, Client62::INULL,
			Client62::INULL, Client62::INULL, Client62::INULL,
			Client62::INULL
		),

		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,

		false,
		false,
		false,
		false
	),
	/*[MobVersion::Titanium] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE,          Titanium::invtype::BANK_SIZE,          Titanium::invtype::SHARED_BANK_SIZE,
			Titanium::invtype::TRADE_SIZE,          Titanium::invtype::WORLD_SIZE,         Titanium::invtype::LIMBO_SIZE,
			Titanium::invtype::TRIBUTE_SIZE,        Titanium::invtype::GUILD_TRIBUTE_SIZE, Titanium::invtype::MERCHANT_SIZE,
			Titanium::invtype::CORPSE_SIZE,         Titanium::invtype::BAZAAR_SIZE,        Titanium::invtype::INSPECT_SIZE,
			Titanium::invtype::VIEW_MOD_PC_SIZE,    Titanium::invtype::VIEW_MOD_BANK_SIZE, Titanium::invtype::VIEW_MOD_SHARED_BANK_SIZE,
			Titanium::invtype::VIEW_MOD_LIMBO_SIZE, Titanium::invtype::ALT_STORAGE_SIZE,   Titanium::invtype::ARCHIVED_SIZE,
			Titanium::invtype::OTHER_SIZE
		),

		Titanium::invslot::EQUIPMENT_BITMASK,
		Titanium::invslot::GENERAL_BITMASK,
		Titanium::invslot::CURSOR_BITMASK,
		Titanium::invslot::POSSESSIONS_BITMASK,
		Titanium::invslot::CORPSE_BITMASK,
		Titanium::invbag::SLOT_COUNT,
		Titanium::invaug::SOCKET_COUNT,

		Titanium::inventory::AllowEmptyBagInBag,
		Titanium::inventory::AllowClickCastFromBag,
		Titanium::inventory::ConcatenateInvTypeLimbo,
		Titanium::inventory::AllowOverLevelEquipment
	),
	/*[MobVersion::SoF] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE,     SoF::invtype::BANK_SIZE,          SoF::invtype::SHARED_BANK_SIZE,
			SoF::invtype::TRADE_SIZE,          SoF::invtype::WORLD_SIZE,         SoF::invtype::LIMBO_SIZE,
			SoF::invtype::TRIBUTE_SIZE,        SoF::invtype::GUILD_TRIBUTE_SIZE, SoF::invtype::MERCHANT_SIZE,
			SoF::invtype::CORPSE_SIZE,         SoF::invtype::BAZAAR_SIZE,        SoF::invtype::INSPECT_SIZE,
			SoF::invtype::VIEW_MOD_PC_SIZE,    SoF::invtype::VIEW_MOD_BANK_SIZE, SoF::invtype::VIEW_MOD_SHARED_BANK_SIZE,
			SoF::invtype::VIEW_MOD_LIMBO_SIZE, SoF::invtype::ALT_STORAGE_SIZE,   SoF::invtype::ARCHIVED_SIZE,
			SoF::invtype::OTHER_SIZE
		),

		SoF::invslot::EQUIPMENT_BITMASK,
		SoF::invslot::GENERAL_BITMASK,
		SoF::invslot::CURSOR_BITMASK,
		SoF::invslot::POSSESSIONS_BITMASK,
		SoF::invslot::CORPSE_BITMASK,
		SoF::invbag::SLOT_COUNT,
		SoF::invaug::SOCKET_COUNT,

		SoF::inventory::AllowEmptyBagInBag,
		SoF::inventory::AllowClickCastFromBag,
		SoF::inventory::ConcatenateInvTypeLimbo,
		SoF::inventory::AllowOverLevelEquipment
	),
	/*[MobVersion::SoD] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE,     SoD::invtype::BANK_SIZE,          SoD::invtype::SHARED_BANK_SIZE,
			SoD::invtype::TRADE_SIZE,          SoD::invtype::WORLD_SIZE,         SoD::invtype::LIMBO_SIZE,
			SoD::invtype::TRIBUTE_SIZE,        SoD::invtype::GUILD_TRIBUTE_SIZE, SoD::invtype::MERCHANT_SIZE,
			SoD::invtype::CORPSE_SIZE,         SoD::invtype::BAZAAR_SIZE,        SoD::invtype::INSPECT_SIZE,
			SoD::invtype::VIEW_MOD_PC_SIZE,    SoD::invtype::VIEW_MOD_BANK_SIZE, SoD::invtype::VIEW_MOD_SHARED_BANK_SIZE,
			SoD::invtype::VIEW_MOD_LIMBO_SIZE, SoD::invtype::ALT_STORAGE_SIZE,   SoD::invtype::ARCHIVED_SIZE,
			SoD::invtype::OTHER_SIZE
		),

		SoD::invslot::EQUIPMENT_BITMASK,
		SoD::invslot::GENERAL_BITMASK,
		SoD::invslot::CURSOR_BITMASK,
		SoD::invslot::POSSESSIONS_BITMASK,
		SoD::invslot::CORPSE_BITMASK,
		SoD::invbag::SLOT_COUNT,
		SoD::invaug::SOCKET_COUNT,

		SoD::inventory::AllowEmptyBagInBag,
		SoD::inventory::AllowClickCastFromBag,
		SoD::inventory::ConcatenateInvTypeLimbo,
		SoD::inventory::AllowOverLevelEquipment
	),
	/*[MobVersion::NPC] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE,		    EntityLimits::NPC::INULL,	EntityLimits::NPC::INULL,
			EntityLimits::NPC::invtype::TRADE_SIZE, EntityLimits::NPC::INULL,	EntityLimits::NPC::INULL,
			EntityLimits::NPC::INULL,				EntityLimits::NPC::INULL,	EntityLimits::NPC::INULL,
			EntityLimits::NPC::INULL,				EntityLimits::NPC::INULL,	EntityLimits::NPC::INULL,
			EntityLimits::NPC::INULL,				EntityLimits::NPC::INULL,	EntityLimits::NPC::INULL,
			EntityLimits::NPC::INULL,				EntityLimits::NPC::INULL,	EntityLimits::NPC::INULL,
			EntityLimits::NPC::INULL
		),

		EntityLimits::NPC::INULL,
		EntityLimits::NPC::INULL,
		EntityLimits::NPC::INULL,
		EntityLimits::NPC::INULL,
		EntityLimits::NPC::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		0, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::NPCMerchant] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE, /*InvTypePossessionsSize,*/	    EntityLimits::NPCMerchant::INULL,	EntityLimits::NPCMerchant::INULL,
			EntityLimits::NPCMerchant::invtype::TRADE_SIZE,					EntityLimits::NPCMerchant::INULL,	EntityLimits::NPCMerchant::INULL,
			EntityLimits::NPCMerchant::INULL,								EntityLimits::NPCMerchant::INULL,	EntityLimits::NPCMerchant::INULL,
			EntityLimits::NPCMerchant::INULL,								EntityLimits::NPCMerchant::INULL,	EntityLimits::NPCMerchant::INULL,
			EntityLimits::NPCMerchant::INULL,								EntityLimits::NPCMerchant::INULL,	EntityLimits::NPCMerchant::INULL,
			EntityLimits::NPCMerchant::INULL,								EntityLimits::NPCMerchant::INULL,	EntityLimits::NPCMerchant::INULL,
			EntityLimits::NPCMerchant::INULL
		),

		EntityLimits::NPCMerchant::INULL,
		EntityLimits::NPCMerchant::INULL,
		EntityLimits::NPCMerchant::INULL,
		EntityLimits::NPCMerchant::INULL,
		EntityLimits::NPCMerchant::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		0, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::Merc] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE, /*InvTypePossessionsSize,*/		EntityLimits::Merc::INULL,	EntityLimits::Merc::INULL,
			EntityLimits::Merc::invtype::TRADE_SIZE,						EntityLimits::Merc::INULL,	EntityLimits::Merc::INULL,
			EntityLimits::Merc::INULL,										EntityLimits::Merc::INULL,  EntityLimits::Merc::INULL,																	
			EntityLimits::Merc::INULL,										EntityLimits::Merc::INULL,	EntityLimits::Merc::INULL,
			EntityLimits::Merc::INULL,										EntityLimits::Merc::INULL,	EntityLimits::Merc::INULL,
			EntityLimits::Merc::INULL,										EntityLimits::Merc::INULL,	EntityLimits::Merc::INULL,
			EntityLimits::Merc::INULL
		),

		EntityLimits::Merc::INULL,
		EntityLimits::Merc::INULL,
		EntityLimits::Merc::INULL,
		EntityLimits::Merc::INULL,
		EntityLimits::Merc::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		0, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::Bot] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE, /*InvTypePossessionsSize,*/		EntityLimits::Bot::INULL,	EntityLimits::Bot::INULL,
			EntityLimits::Bot::invtype::TRADE_SIZE,							EntityLimits::Bot::INULL,	EntityLimits::Bot::INULL,
			EntityLimits::Bot::INULL,										EntityLimits::Bot::INULL,	EntityLimits::Bot::INULL,
			EntityLimits::Bot::INULL,										EntityLimits::Bot::INULL,	EntityLimits::Bot::INULL,
			EntityLimits::Bot::INULL,										EntityLimits::Bot::INULL,	EntityLimits::Bot::INULL,
			EntityLimits::Bot::INULL,										EntityLimits::Bot::INULL,	EntityLimits::Bot::INULL,
			EntityLimits::Bot::INULL
		),

		EntityLimits::Bot::invslot::EQUIPMENT_BITMASK,
		EntityLimits::Bot::invslot::GENERAL_BITMASK,
		EntityLimits::Bot::invslot::CURSOR_BITMASK,
		EntityLimits::Bot::invslot::POSSESSIONS_BITMASK,
		EntityLimits::Bot::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		EQ::invaug::SOCKET_COUNT, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::ClientPet] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE, /*InvTypePossessionsSize,*/		EntityLimits::ClientPet::INULL,	EntityLimits::ClientPet::INULL,
			EntityLimits::ClientPet::invtype::TRADE_SIZE,					EntityLimits::ClientPet::INULL, EntityLimits::ClientPet::INULL,
			EntityLimits::ClientPet::INULL,									EntityLimits::ClientPet::INULL,	EntityLimits::ClientPet::INULL,		
			EntityLimits::ClientPet::INULL,									EntityLimits::ClientPet::INULL,	EntityLimits::ClientPet::INULL,
			EntityLimits::ClientPet::INULL,									EntityLimits::ClientPet::INULL,	EntityLimits::ClientPet::INULL,
			EntityLimits::ClientPet::INULL,									EntityLimits::ClientPet::INULL,	EntityLimits::ClientPet::INULL,
			EntityLimits::ClientPet::INULL
		),

		EntityLimits::ClientPet::INULL,
		EntityLimits::ClientPet::INULL,
		EntityLimits::ClientPet::INULL,
		EntityLimits::ClientPet::INULL,
		EntityLimits::ClientPet::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		0, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::NPCPet] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE, /*InvTypePossessionsSize,*/	    EntityLimits::NPCPet::INULL,	EntityLimits::NPCPet::INULL,
			EntityLimits::NPCPet::invtype::TRADE_SIZE,						EntityLimits::NPCPet::INULL,	EntityLimits::NPCPet::INULL,
			EntityLimits::NPCPet::INULL,									EntityLimits::NPCPet::INULL,	EntityLimits::NPCPet::INULL,	
			EntityLimits::NPCPet::INULL,									EntityLimits::NPCPet::INULL,	EntityLimits::NPCPet::INULL,
			EntityLimits::NPCPet::INULL,									EntityLimits::NPCPet::INULL,	EntityLimits::NPCPet::INULL,
			EntityLimits::NPCPet::INULL,									EntityLimits::NPCPet::INULL,	EntityLimits::NPCPet::INULL,
			EntityLimits::NPCPet::INULL
		),

		EntityLimits::NPCPet::INULL,
		EntityLimits::NPCPet::INULL,
		EntityLimits::NPCPet::INULL,
		EntityLimits::NPCPet::INULL,
		EntityLimits::NPCPet::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		0, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::MercPet] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE, /*InvTypePossessionsSize,*/		EntityLimits::MercPet::INULL,	EntityLimits::MercPet::INULL,
			EntityLimits::MercPet::invtype::TRADE_SIZE,						EntityLimits::MercPet::INULL,	EntityLimits::MercPet::INULL,
			EntityLimits::MercPet::INULL,									EntityLimits::MercPet::INULL,	EntityLimits::MercPet::INULL,
			EntityLimits::MercPet::INULL,									EntityLimits::MercPet::INULL,	EntityLimits::MercPet::INULL,
			EntityLimits::MercPet::INULL,									EntityLimits::MercPet::INULL,	EntityLimits::MercPet::INULL,
			EntityLimits::MercPet::INULL,									EntityLimits::MercPet::INULL,	EntityLimits::MercPet::INULL,
			EntityLimits::MercPet::INULL
		),

		EntityLimits::MercPet::INULL,
		EntityLimits::MercPet::INULL,
		EntityLimits::MercPet::INULL,
		EntityLimits::MercPet::INULL,
		EntityLimits::MercPet::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		0, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::BotPet] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			EQ::invtype::POSSESSIONS_SIZE, /*InvTypePossessionsSize,*/		EntityLimits::BotPet::INULL,	EntityLimits::BotPet::INULL,
			EntityLimits::BotPet::invtype::TRADE_SIZE,						EntityLimits::BotPet::INULL,	EntityLimits::BotPet::INULL,
			EntityLimits::BotPet::INULL,									EntityLimits::BotPet::INULL,	EntityLimits::BotPet::INULL,
			EntityLimits::BotPet::INULL,									EntityLimits::BotPet::INULL,	EntityLimits::BotPet::INULL,
			EntityLimits::BotPet::INULL,									EntityLimits::BotPet::INULL,	EntityLimits::BotPet::INULL,
			EntityLimits::BotPet::INULL,									EntityLimits::BotPet::INULL,	EntityLimits::BotPet::INULL,
			EntityLimits::BotPet::INULL
		),

		EntityLimits::BotPet::INULL,
		EntityLimits::BotPet::INULL,
		EntityLimits::BotPet::INULL,
		EntityLimits::BotPet::INULL,
		EntityLimits::BotPet::INULL,
		0, //EQ::inventory::ContainerCount, /*ItemBagSize,*/
		0, //EQ::inventory::SocketCount, /*ItemAugSize,*/

		false,
		false,
		false,
		false
	),
	/*[MobVersion::OfflineTitanium] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			Titanium::INULL,						Titanium::INULL,						Titanium::INULL,
			Titanium::invtype::TRADE_SIZE,			Titanium::INULL,						Titanium::INULL,
			Titanium::INULL,						Titanium::INULL,						Titanium::invtype::MERCHANT_SIZE,
			Titanium::INULL,						Titanium::invtype::BAZAAR_SIZE,			Titanium::invtype::INSPECT_SIZE,
			Titanium::invtype::VIEW_MOD_PC_SIZE,	Titanium::invtype::VIEW_MOD_BANK_SIZE,	Titanium::invtype::VIEW_MOD_SHARED_BANK_SIZE,
			Titanium::invtype::VIEW_MOD_LIMBO_SIZE,	Titanium::INULL,						Titanium::INULL,
			Titanium::INULL
		),

		Titanium::INULL,
		Titanium::INULL,
		Titanium::INULL,
		Titanium::INULL,
		Titanium::INULL,
		Titanium::invbag::SLOT_COUNT,
		Titanium::invaug::SOCKET_COUNT,

		false,
		false,
		false,
		false
	),
	/*[MobVersion::OfflineSoF] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			SoF::INULL,							SoF::INULL,							SoF::INULL,
			SoF::invtype::TRADE_SIZE,			SoF::INULL,							SoF::INULL,
			SoF::INULL,							SoF::INULL,							SoF::invtype::MERCHANT_SIZE,
			SoF::INULL,							SoF::invtype::BAZAAR_SIZE,			SoF::invtype::INSPECT_SIZE,
			SoF::invtype::VIEW_MOD_PC_SIZE,		SoF::invtype::VIEW_MOD_BANK_SIZE,	SoF::invtype::VIEW_MOD_SHARED_BANK_SIZE,
			SoF::invtype::VIEW_MOD_LIMBO_SIZE,	SoF::INULL,							SoF::INULL,
			SoF::INULL
		),

		SoF::INULL,
		SoF::INULL,
		SoF::INULL,
		SoF::INULL,
		SoF::INULL,
		SoF::invbag::SLOT_COUNT,
		SoF::invaug::SOCKET_COUNT,

		false,
		false,
		false,
		false
	),
	/*[MobVersion::OfflineSoD] =*/
	EQ::inventory::LookupEntry(
		EQ::inventory::LookupEntry::InventoryTypeSize_Struct(
			SoD::INULL,							SoD::INULL,							SoD::INULL,
			SoD::invtype::TRADE_SIZE,			SoD::INULL,							SoD::INULL,
			SoD::INULL,							SoD::INULL,							SoD::invtype::MERCHANT_SIZE,
			SoD::INULL,							SoD::invtype::BAZAAR_SIZE,			SoD::invtype::INSPECT_SIZE,
			SoD::invtype::VIEW_MOD_PC_SIZE,		SoD::invtype::VIEW_MOD_BANK_SIZE,	SoD::invtype::VIEW_MOD_SHARED_BANK_SIZE,
			SoD::invtype::VIEW_MOD_LIMBO_SIZE,	SoD::INULL,							SoD::INULL,
			SoD::INULL
		),

		SoD::INULL,
		SoD::INULL,
		SoD::INULL,
		SoD::INULL,
		SoD::INULL,
		SoD::invbag::SLOT_COUNT,
		SoD::invaug::SOCKET_COUNT,

		false,
		false,
		false,
		false
	)
};

static bool inventory_dictionary_init = false;
void EQ::inventory::InitializeDynamicLookups() {
	if (inventory_dictionary_init == true)
		return;
	inventory_dictionary_init = true;

	// server is configured for static definitions
	if (RuleB(World, UseClientBasedExpansionSettings))
		return;

	// Notes:
	// - Currently, there are only 3 known expansions that affect inventory-related settings in the clients..
	//   -- Expansion::PoR "Prophecy of Ro" - toggles between 24 (set) and 16 (clear) bank slots
	//   -- Expansion::TBS "The Buried Sea" - toggles slotPowerSource activated (set) and deactivated (clear)
	//   -- Expansion::HoT "House of Thule" - toggles slotGeneral9/slotGeneral10 activated (set) and deactivated (clear)
	// - Corspe size does not appear to reflect loss of active possessions slots
	// - Inspect size does not appear to reflect loss of active equipment slots
	// - Bank size is not overridden by GM flag when expansion bit is (clear)
	// - Power Source slot is enabled, but not activated, by GM flag when expansion bit is (clear) (RoF+ only)
	// - General9 and General10 slots are activated by GM flag when expansion bit is (clear)
	// - Obviously, the client must support the expansion to allow any (set) or override condition

	const uint32 dynamic_check_mask =
		(
			EQ::expansions::bitPoR |
			EQ::expansions::bitTBS
		);

	// if all of the above expansion bits are present, then static references will suffice
	if ((dynamic_check_mask & RuleI(World, ExpansionSettings)) == dynamic_check_mask)
		return;

	// Dynamic Lookups (promotive methodology) (all mob versions allowed)
	for (uint32 iter = static_cast<uint32>(EQ::versions::MobVersion::Unknown); iter <= static_cast<uint32>(EQ::versions::LastPCMobVersion); ++iter) {
		// no need to dynamic this condition since it is the lowest compatibility standard
		if ((dynamic_check_mask & ~constants_static_lookup_entries[iter].ExpansionsMask) == dynamic_check_mask)
			continue;

		// only client versions whose supported expansions are affected need to be considered
		if ((constants_static_lookup_entries[iter].ExpansionsMask & RuleI(World, ExpansionSettings)) == constants_static_lookup_entries[iter].ExpansionsMask)
			continue;

		// direct manipulation of lookup indices is safe so long as (int)ClientVersion::<mob> == (int)MobVersion::<mob>
		inventory_dynamic_nongm_lookup_entries[iter] = std::make_unique<LookupEntry>(inventory_static_lookup_entries[iter]);

		// clamp affected fields to the lowest standard
		inventory_dynamic_nongm_lookup_entries[iter]->InventoryTypeSize.Bank = Titanium::invtype::BANK_SIZE; // bank size
		inventory_dynamic_nongm_lookup_entries[iter]->EquipmentBitmask = Titanium::invslot::EQUIPMENT_BITMASK; // power source
		inventory_dynamic_nongm_lookup_entries[iter]->GeneralBitmask = Titanium::invslot::GENERAL_BITMASK; // general size
		inventory_dynamic_nongm_lookup_entries[iter]->PossessionsBitmask = 0; // we'll fix later
		inventory_dynamic_nongm_lookup_entries[iter]->CorpseBitmask = 0; // we'll fix later

		if (RuleI(World, ExpansionSettings) & EQ::expansions::bitPoR) {
			// update bank size
			if (constants_static_lookup_entries[iter].ExpansionsMask & EQ::expansions::bitPoR)
				inventory_dynamic_nongm_lookup_entries[iter]->InventoryTypeSize.Bank = SoF::invtype::BANK_SIZE;
		}

		if (RuleI(World, ExpansionSettings) & EQ::expansions::bitTBS) {
			// update power source
			if (constants_static_lookup_entries[iter].ExpansionsMask & EQ::expansions::bitTBS)
				inventory_dynamic_nongm_lookup_entries[iter]->EquipmentBitmask = SoF::invslot::EQUIPMENT_BITMASK;
		}


		// fixup possessions bitmask
		inventory_dynamic_nongm_lookup_entries[iter]->PossessionsBitmask =
			(
				inventory_dynamic_nongm_lookup_entries[iter]->EquipmentBitmask |
				inventory_dynamic_nongm_lookup_entries[iter]->GeneralBitmask |
				inventory_dynamic_nongm_lookup_entries[iter]->CursorBitmask
			);

		// fixup corpse bitmask
		inventory_dynamic_nongm_lookup_entries[iter]->CorpseBitmask =
			(
				inventory_dynamic_nongm_lookup_entries[iter]->GeneralBitmask |
				inventory_dynamic_nongm_lookup_entries[iter]->CursorBitmask |
				(inventory_dynamic_nongm_lookup_entries[iter]->EquipmentBitmask << 34)
			);

		// expansion-related fields are now updated and all other fields reflect the static entry values
	}

	// Dynamic GM Lookups (demotive methodology) (client-linked mob versions only)
	for (uint32 iter = static_cast<uint32>(EQ::versions::MobVersion::Unknown); iter <= static_cast<uint32>(EQ::versions::LastPCMobVersion); ++iter) {
		// no need to dynamic this condition since it is the lowest compatibility standard
		if ((dynamic_check_mask & ~constants_static_lookup_entries[iter].ExpansionsMask) == dynamic_check_mask)
			continue;

		// only client versions whose supported expansions are affected need to be considered
		if ((constants_static_lookup_entries[iter].ExpansionsMask & RuleI(World, ExpansionSettings)) == constants_static_lookup_entries[iter].ExpansionsMask)
			continue;

		// direct manipulation of lookup indices is safe so long as (int)ClientVersion::<client> == (int)MobVersion::<client>
		inventory_dynamic_gm_lookup_entries[iter] = std::make_unique<LookupEntry>(inventory_static_lookup_entries[iter]);

		inventory_dynamic_gm_lookup_entries[iter]->PossessionsBitmask = 0; // we'll fix later
		inventory_dynamic_gm_lookup_entries[iter]->CorpseBitmask = 0; // we'll fix later

		if (~RuleI(World, ExpansionSettings) & EQ::expansions::bitPoR) {
			// update bank size
			if (constants_static_lookup_entries[iter].ExpansionsMask & EQ::expansions::bitPoR)
				inventory_dynamic_gm_lookup_entries[iter]->InventoryTypeSize.Bank = Titanium::invtype::BANK_SIZE;
		}

		if (~RuleI(World, ExpansionSettings) & EQ::expansions::bitTBS) {
			// update power source
			switch (iter) {
			case versions::bitSoD:
			case versions::bitSoF:
				// gm flag does not override expansion-based behavior
				// (we already know that only these clients support this behavior)
				inventory_dynamic_gm_lookup_entries[iter]->EquipmentBitmask = Titanium::invslot::EQUIPMENT_BITMASK;
				break;
			default:
				break;
			}
		}

		// fixup possessions bitmask
		inventory_dynamic_gm_lookup_entries[iter]->PossessionsBitmask =
			(
				inventory_dynamic_gm_lookup_entries[iter]->EquipmentBitmask |
				inventory_dynamic_gm_lookup_entries[iter]->GeneralBitmask |
				inventory_dynamic_gm_lookup_entries[iter]->CursorBitmask
			);

		// fixup corpse bitmask
		inventory_dynamic_gm_lookup_entries[iter]->CorpseBitmask =
			(
				inventory_dynamic_gm_lookup_entries[iter]->GeneralBitmask |
				inventory_dynamic_gm_lookup_entries[iter]->CursorBitmask |
				(inventory_dynamic_gm_lookup_entries[iter]->EquipmentBitmask << 34)
			);

		// expansion-related fields are now updated and all other fields reflect the static entry values
	}

	// only client versions that require a change from their static definitions have been given a dynamic (gm) lookup entry
}

const EQ::inventory::LookupEntry* EQ::inventory::DynamicLookup(versions::MobVersion mob_version, bool gm_flag)
{
	if (gm_flag)
		return DynamicGMLookup(mob_version);
	else
		return DynamicNonGMLookup(mob_version);
}

const EQ::inventory::LookupEntry* EQ::inventory::DynamicNonGMLookup(versions::MobVersion mob_version)
{
	mob_version = versions::ValidateMobVersion(mob_version);
	if (inventory_dynamic_nongm_lookup_entries[static_cast<int>(mob_version)])
		return inventory_dynamic_nongm_lookup_entries[static_cast<int>(mob_version)].get();

	return &inventory_static_lookup_entries[static_cast<int>(mob_version)];
}

const EQ::inventory::LookupEntry* EQ::inventory::DynamicGMLookup(versions::MobVersion mob_version)
{
	mob_version = versions::ValidateMobVersion(mob_version);
	if (inventory_dynamic_gm_lookup_entries[static_cast<int>(mob_version)])
		return inventory_dynamic_gm_lookup_entries[static_cast<int>(mob_version)].get();

	return &inventory_static_lookup_entries[static_cast<int>(mob_version)];
}

const EQ::inventory::LookupEntry* EQ::inventory::StaticLookup(versions::MobVersion mob_version)
{
	return &inventory_static_lookup_entries[static_cast<int>(versions::ValidateMobVersion(mob_version))];
}

static std::unique_ptr<EQ::behavior::LookupEntry> behavior_dynamic_nongm_lookup_entries[EQ::versions::MobVersionCount];
static std::unique_ptr<EQ::behavior::LookupEntry> behavior_dynamic_gm_lookup_entries[EQ::versions::MobVersionCount];
static const EQ::behavior::LookupEntry behavior_static_lookup_entries[EQ::versions::MobVersionCount] =
{
	/*[MobVersion::Unknown] =*/
	EQ::behavior::LookupEntry(
		true
	),
	/*[MobVersion::Client62] =*/
	EQ::behavior::LookupEntry(
		true
	),
	/*[MobVersion::Titanium] =*/
	EQ::behavior::LookupEntry(
		Titanium::behavior::CoinHasWeight
	),
	/*[MobVersion::SoF] =*/
	EQ::behavior::LookupEntry(
		SoF::behavior::CoinHasWeight
	),
	/*[MobVersion::SoD] =*/
	EQ::behavior::LookupEntry(
		SoD::behavior::CoinHasWeight
	),
	/*[MobVersion::NPC] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::NPCMerchant] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::Merc] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::Bot] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::ClientPet] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::NPCPet] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::MercPet] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::BotPet] =*/
	EQ::behavior::LookupEntry(
		EQ::behavior::CoinHasWeight
	),
	/*[MobVersion::OfflineTitanium] =*/
	EQ::behavior::LookupEntry(
		Titanium::behavior::CoinHasWeight
	),
	/*[MobVersion::OfflineSoF] =*/
	EQ::behavior::LookupEntry(
		SoF::behavior::CoinHasWeight
	),
	/*[MobVersion::OfflineSoD] =*/
	EQ::behavior::LookupEntry(
		SoD::behavior::CoinHasWeight
	)
};

static bool behavior_dictionary_init = false;
void EQ::behavior::InitializeDynamicLookups() {
	if (behavior_dictionary_init == true)
		return;
	behavior_dictionary_init = true;

	if (RuleB(World, UseClientBasedExpansionSettings))
		return;

	// use static references for now
}

const EQ::behavior::LookupEntry* EQ::behavior::DynamicLookup(versions::MobVersion mob_version, bool gm_flag)
{
	if (gm_flag)
		return DynamicGMLookup(mob_version);
	else
		return DynamicNonGMLookup(mob_version);
}

const EQ::behavior::LookupEntry* EQ::behavior::DynamicNonGMLookup(versions::MobVersion mob_version)
{
	mob_version = versions::ValidateMobVersion(mob_version);
	if (behavior_dynamic_nongm_lookup_entries[static_cast<int>(mob_version)])
		return behavior_dynamic_nongm_lookup_entries[static_cast<int>(mob_version)].get();

	return &behavior_static_lookup_entries[static_cast<int>(mob_version)];
}

const EQ::behavior::LookupEntry* EQ::behavior::DynamicGMLookup(versions::MobVersion mob_version)
{
	mob_version = versions::ValidateMobVersion(mob_version);
	if (behavior_dynamic_gm_lookup_entries[static_cast<int>(mob_version)])
		return behavior_dynamic_gm_lookup_entries[static_cast<int>(mob_version)].get();

	return &behavior_static_lookup_entries[static_cast<int>(mob_version)];
}

const EQ::behavior::LookupEntry* EQ::behavior::StaticLookup(versions::MobVersion mob_version)
{
	return &behavior_static_lookup_entries[static_cast<int>(versions::ValidateMobVersion(mob_version))];
}

static std::unique_ptr<EQ::spells::LookupEntry> spells_dynamic_nongm_lookup_entries[EQ::versions::ClientVersionCount];
static std::unique_ptr<EQ::spells::LookupEntry> spells_dynamic_gm_lookup_entries[EQ::versions::ClientVersionCount];
static const EQ::spells::LookupEntry spells_static_lookup_entries[EQ::versions::ClientVersionCount] =
{
	/*[ClientVersion::Unknown] =*/
	EQ::spells::LookupEntry(
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL,
		ClientUnknown::INULL
	),
	/*[ClientVersion::Client62] =*/
	EQ::spells::LookupEntry(
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL,
		Client62::INULL
	),
	/*[ClientVersion::Titanium] =*/
	EQ::spells::LookupEntry(
		Titanium::spells::SPELL_ID_MAX,
		Titanium::spells::SPELLBOOK_SIZE,
		Titanium::spells::SPELL_GEM_COUNT,
		Titanium::spells::LONG_BUFFS,
		Titanium::spells::SHORT_BUFFS,
		Titanium::spells::DISC_BUFFS,
		Titanium::spells::TOTAL_BUFFS,
		Titanium::spells::NPC_BUFFS,
		Titanium::spells::PET_BUFFS,
		Titanium::spells::MERC_BUFFS
	),
	/*[ClientVersion::SoF] =*/
	EQ::spells::LookupEntry(
		SoF::spells::SPELL_ID_MAX,
		SoF::spells::SPELLBOOK_SIZE,
		SoF::spells::SPELL_GEM_COUNT,
		SoF::spells::LONG_BUFFS,
		SoF::spells::SHORT_BUFFS,
		SoF::spells::DISC_BUFFS,
		SoF::spells::TOTAL_BUFFS,
		SoF::spells::NPC_BUFFS,
		SoF::spells::PET_BUFFS,
		SoF::spells::MERC_BUFFS
	),
	/*[ClientVersion::SoD] =*/
	EQ::spells::LookupEntry(
		SoD::spells::SPELL_ID_MAX,
		SoD::spells::SPELLBOOK_SIZE,
		SoD::spells::SPELL_GEM_COUNT,
		SoD::spells::LONG_BUFFS,
		SoD::spells::SHORT_BUFFS,
		SoD::spells::DISC_BUFFS,
		SoD::spells::TOTAL_BUFFS,
		SoD::spells::NPC_BUFFS,
		SoD::spells::PET_BUFFS,
		SoD::spells::MERC_BUFFS
	)
};

static bool spells_dictionary_init = false;
void EQ::spells::InitializeDynamicLookups() {
	if (spells_dictionary_init == true)
		return;
	spells_dictionary_init = true;

	if (RuleB(World, UseClientBasedExpansionSettings))
		return;

	// use static references for now
}

const EQ::spells::LookupEntry* EQ::spells::DynamicLookup(versions::ClientVersion client_version, bool gm_flag)
{
	if (gm_flag)
		return DynamicGMLookup(client_version);
	else
		return DynamicNonGMLookup(client_version);
}

const EQ::spells::LookupEntry* EQ::spells::DynamicNonGMLookup(versions::ClientVersion client_version)
{
	client_version = versions::ValidateClientVersion(client_version);
	if (spells_dynamic_nongm_lookup_entries[static_cast<int>(client_version)])
		return spells_dynamic_nongm_lookup_entries[static_cast<int>(client_version)].get();

	return &spells_static_lookup_entries[static_cast<int>(client_version)];
}

const EQ::spells::LookupEntry* EQ::spells::DynamicGMLookup(versions::ClientVersion client_version)
{
	client_version = versions::ValidateClientVersion(client_version);
	if (spells_dynamic_gm_lookup_entries[static_cast<int>(client_version)])
		return spells_dynamic_gm_lookup_entries[static_cast<int>(client_version)].get();

	return &spells_static_lookup_entries[static_cast<int>(client_version)];
}

const EQ::spells::LookupEntry* EQ::spells::StaticLookup(versions::ClientVersion client_version)
{
	return &spells_static_lookup_entries[static_cast<int>(versions::ValidateClientVersion(client_version))];
}
