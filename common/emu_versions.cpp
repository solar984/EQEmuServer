/*	EQEMu: Everquest Server Emulator
	
	Copyright (C) 2001-2016 EQEMu Development Team (http://eqemulator.net)

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; version 2 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY except by those people which sell it, which
	are required to give you total support for your newly bought product;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "emu_versions.h"
#include "emu_constants.h"


bool EQ::versions::IsValidClientVersion(ClientVersion client_version)
{
	if (client_version <= ClientVersion::Unknown || client_version > LastClientVersion)
		return false;

	return true;
}

EQ::versions::ClientVersion EQ::versions::ValidateClientVersion(ClientVersion client_version)
{
	if (client_version <= ClientVersion::Unknown || client_version > LastClientVersion)
		return ClientVersion::Unknown;

	return client_version;
}

const char* EQ::versions::ClientVersionName(ClientVersion client_version)
{
	switch (client_version) {
	case ClientVersion::Unknown:
		return "Unknown Version";
	case ClientVersion::Client62:
		return "Client 6.2";
	case ClientVersion::Titanium:
		return "Titanium";
	default:
		return "Invalid Version";
	};
}

uint32 EQ::versions::ConvertClientVersionToClientVersionBit(ClientVersion client_version)
{
	switch (client_version) {
	case ClientVersion::Titanium:
		return bitTitanium;
	default:
		return bitUnknown;
	}
}

EQ::versions::ClientVersion EQ::versions::ConvertClientVersionBitToClientVersion(uint32 client_version_bit)
{
	switch (client_version_bit) {
	case ((uint32)1 << (static_cast<unsigned int>(ClientVersion::Titanium) - 1)) :
		return ClientVersion::Titanium;
	default:
		return ClientVersion::Unknown;
	}
}

bool EQ::versions::IsValidMobVersion(MobVersion mob_version)
{
	if (mob_version <= MobVersion::Unknown || mob_version > LastMobVersion)
		return false;

	return true;
}

bool EQ::versions::IsValidPCMobVersion(MobVersion mob_version)
{
	if (mob_version <= MobVersion::Unknown || mob_version > LastPCMobVersion)
		return false;

	return true;
}

bool EQ::versions::IsValidNonPCMobVersion(MobVersion mob_version)
{
	if (mob_version <= LastPCMobVersion || mob_version > LastNonPCMobVersion)
		return false;

	return true;
}

bool EQ::versions::IsValidOfflinePCMobVersion(MobVersion mob_version)
{
	if (mob_version <= LastNonPCMobVersion || mob_version > LastOfflinePCMobVersion)
		return false;

	return true;
}

EQ::versions::MobVersion EQ::versions::ValidateMobVersion(MobVersion mob_version)
{
	if (mob_version <= MobVersion::Unknown || mob_version > LastMobVersion)
		return MobVersion::Unknown;

	return mob_version;
}

EQ::versions::MobVersion EQ::versions::ValidatePCMobVersion(MobVersion mob_version)
{
	if (mob_version <= MobVersion::Unknown || mob_version > LastPCMobVersion)
		return MobVersion::Unknown;

	return mob_version;
}

EQ::versions::MobVersion EQ::versions::ValidateNonPCMobVersion(MobVersion mob_version)
{
	if (mob_version <= LastPCMobVersion || mob_version > LastNonPCMobVersion)
		return MobVersion::Unknown;

	return mob_version;
}

EQ::versions::MobVersion EQ::versions::ValidateOfflinePCMobVersion(MobVersion mob_version)
{
	if (mob_version <= LastNonPCMobVersion || mob_version > LastOfflinePCMobVersion)
		return MobVersion::Unknown;

	return mob_version;
}

const char* EQ::versions::MobVersionName(MobVersion mob_version)
{
	switch (mob_version) {
	case MobVersion::Unknown:
		return "Unknown Version";
	case MobVersion::Client62:
		return "Client 6.2";
	case MobVersion::Titanium:
		return "Titanium";
	case MobVersion::NPC:
		return "NPC";
	case MobVersion::NPCMerchant:
		return "NPC Merchant";
	case MobVersion::Bot:
		return "Bot";
	case MobVersion::ClientPet:
		return "Client Pet";
	case MobVersion::NPCPet:
		return "NPC Pet";
	case MobVersion::BotPet:
		return "Bot Pet";
	case MobVersion::OfflineTitanium:
		return "Offline Titanium";
	default:
		return "Invalid Version";
	};
}

EQ::versions::ClientVersion EQ::versions::ConvertMobVersionToClientVersion(MobVersion mob_version)
{
	switch (mob_version) {
	case MobVersion::Unknown:
	case MobVersion::Client62:
		return ClientVersion::Unknown;
	case MobVersion::Titanium:
		return ClientVersion::Titanium;
	default:
		return ClientVersion::Unknown;
	}
}

EQ::versions::MobVersion EQ::versions::ConvertClientVersionToMobVersion(ClientVersion client_version)
{
	switch (client_version) {
	case ClientVersion::Unknown:
	case ClientVersion::Client62:
		return MobVersion::Unknown;
	case ClientVersion::Titanium:
		return MobVersion::Titanium;
	default:
		return MobVersion::Unknown;
	}
}

EQ::versions::MobVersion EQ::versions::ConvertPCMobVersionToOfflinePCMobVersion(MobVersion mob_version)
{
	switch (mob_version) {
	case MobVersion::Titanium:
		return MobVersion::OfflineTitanium;
	default:
		return MobVersion::Unknown;
	}
}

EQ::versions::MobVersion EQ::versions::ConvertOfflinePCMobVersionToPCMobVersion(MobVersion mob_version)
{
	switch (mob_version) {
	case MobVersion::OfflineTitanium:
		return MobVersion::Titanium;
	default:
		return MobVersion::Unknown;
	}
}

EQ::versions::ClientVersion EQ::versions::ConvertOfflinePCMobVersionToClientVersion(MobVersion mob_version)
{
	switch (mob_version) {
	case MobVersion::OfflineTitanium:
		return ClientVersion::Titanium;
	default:
		return ClientVersion::Unknown;
	}
}

EQ::versions::MobVersion EQ::versions::ConvertClientVersionToOfflinePCMobVersion(ClientVersion client_version)
{
	switch (client_version) {
	case ClientVersion::Titanium:
		return MobVersion::OfflineTitanium;
	default:
		return MobVersion::Unknown;
	}
}

const char* EQ::expansions::ExpansionName(Expansion expansion)
{
	switch (expansion) {
	case Expansion::EverQuest:
		return "EverQuest";
	case Expansion::RoK:
		return "The Ruins of Kunark";
	case Expansion::SoV:
		return "The Scars of Velious";
	case Expansion::SoL:
		return "The Shadows of Luclin";
	case Expansion::PoP:
		return "The Planes of Power";
	case Expansion::LoY:
		return "The Legacy of Ykesha";
	case Expansion::LDoN:
		return "Lost Dungeons of Norrath";
	case Expansion::GoD:
		return "Gates of Discord";
	case Expansion::OoW:
		return "Omens of War";
	case Expansion::DoN:
		return "Dragons of Norrath";
	case Expansion::DoD:
		return "Depths of Darkhollow";
	default:
		return "Invalid Expansion";
	}
}

const char* EQ::expansions::ExpansionName(uint32 expansion_bit)
{
	return ExpansionName(ConvertExpansionBitToExpansion(expansion_bit));
}

uint32 EQ::expansions::ConvertExpansionToExpansionBit(Expansion expansion)
{
	switch (expansion) {
	case Expansion::RoK:
		return bitRoK;
	case Expansion::SoV:
		return bitSoV;
	case Expansion::SoL:
		return bitSoL;
	case Expansion::PoP:
		return bitPoP;
	case Expansion::LoY:
		return bitLoY;
	case Expansion::LDoN:
		return bitLDoN;
	case Expansion::GoD:
		return bitGoD;
	case Expansion::OoW:
		return bitOoW;
	case Expansion::DoN:
		return bitDoN;
	case Expansion::DoD:
		return bitDoD;
	default:
		return bitEverQuest;
	}
}

EQ::expansions::Expansion EQ::expansions::ConvertExpansionBitToExpansion(uint32 expansion_bit)
{
	switch (expansion_bit) {
	case bitRoK:
		return Expansion::RoK;
	case bitSoV:
		return Expansion::SoV;
	case bitSoL:
		return Expansion::SoL;
	case bitPoP:
		return Expansion::PoP;
	case bitLoY:
		return Expansion::LoY;
	case bitLDoN:
		return Expansion::LDoN;
	case bitGoD:
		return Expansion::GoD;
	case bitOoW:
		return Expansion::OoW;
	case bitDoN:
		return Expansion::DoN;
	case bitDoD:
		return Expansion::DoD;
	default:
		return Expansion::EverQuest;
	}
}

uint32 EQ::expansions::ConvertExpansionToExpansionsMask(Expansion expansion)
{
	switch (expansion) {
	case Expansion::RoK:
		return maskRoK;
	case Expansion::SoV:
		return maskSoV;
	case Expansion::SoL:
		return maskSoL;
	case Expansion::PoP:
		return maskPoP;
	case Expansion::LoY:
		return maskLoY;
	case Expansion::LDoN:
		return maskLDoN;
	case Expansion::GoD:
		return maskGoD;
	case Expansion::OoW:
		return maskOoW;
	case Expansion::DoN:
		return maskDoN;
	case Expansion::DoD:
		return maskDoD;
	default:
		return maskEverQuest;
	}
}

EQ::expansions::Expansion EQ::expansions::ConvertClientVersionToExpansion(versions::ClientVersion client_version)
{
	return EQ::constants::StaticLookup(client_version)->Expansion;
}

uint32 EQ::expansions::ConvertClientVersionToExpansionBit(versions::ClientVersion client_version)
{
	return EQ::constants::StaticLookup(client_version)->ExpansionBit;
}

uint32 EQ::expansions::ConvertClientVersionToExpansionsMask(versions::ClientVersion client_version)
{
	return EQ::constants::StaticLookup(client_version)->ExpansionsMask;
}
