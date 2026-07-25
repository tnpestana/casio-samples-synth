/*
  ==============================================================================

    SampleData.h
    Created: 19 Sep 2019 7:02:18pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct SampleData
{
public:
    std::pair<const char *, const int> CasioMt40[24] = {
        std::make_pair(BinaryData::_1_wav, BinaryData::_1_wavSize),
        std::make_pair(BinaryData::_2_wav, BinaryData::_2_wavSize),
        std::make_pair(BinaryData::_3_wav, BinaryData::_3_wavSize),
        std::make_pair(BinaryData::_4_wav, BinaryData::_4_wavSize),
        std::make_pair(BinaryData::_5_wav, BinaryData::_5_wavSize),
        std::make_pair(BinaryData::_6_wav, BinaryData::_6_wavSize),
        std::make_pair(BinaryData::_7_wav, BinaryData::_7_wavSize),
        std::make_pair(BinaryData::_8_wav, BinaryData::_8_wavSize),
        std::make_pair(BinaryData::_9_wav, BinaryData::_9_wavSize),
        std::make_pair(BinaryData::_10_wav, BinaryData::_10_wavSize),
        std::make_pair(BinaryData::_11_wav, BinaryData::_11_wavSize),
        std::make_pair(BinaryData::_12_wav, BinaryData::_12_wavSize),
        std::make_pair(BinaryData::_13_wav, BinaryData::_13_wavSize),
        std::make_pair(BinaryData::_14_wav, BinaryData::_14_wavSize),
        std::make_pair(BinaryData::_15_wav, BinaryData::_15_wavSize),
        std::make_pair(BinaryData::_16_wav, BinaryData::_16_wavSize),
        std::make_pair(BinaryData::_17_wav, BinaryData::_17_wavSize),
        std::make_pair(BinaryData::_18_wav, BinaryData::_18_wavSize),
        std::make_pair(BinaryData::_19_wav, BinaryData::_19_wavSize),
        std::make_pair(BinaryData::_20_wav, BinaryData::_20_wavSize),
        std::make_pair(BinaryData::_21_wav, BinaryData::_21_wavSize),
        std::make_pair(BinaryData::_22_wav, BinaryData::_22_wavSize),
        std::make_pair(BinaryData::_23_wav, BinaryData::_23_wavSize),
        std::make_pair(BinaryData::_24_wav, BinaryData::_24_wavSize)
    };
    
    std::pair<const char *, const int> CasioRapman[24] = {
        std::make_pair(BinaryData::RPMN_agogo_wav, BinaryData::RPMN_agogo_wavSize),
        std::make_pair(BinaryData::RPMN_ambulance_wav, BinaryData::RPMN_ambulance_wavSize),
        std::make_pair(BinaryData::RPMN_bandhitbrass_wav, BinaryData::RPMN_bandhitbrass_wavSize),
        std::make_pair(BinaryData::RPMN_bells_wav, BinaryData::RPMN_bells_wavSize),
        std::make_pair(BinaryData::RPMN_brassens_wav, BinaryData::RPMN_brassens_wavSize),
        std::make_pair(BinaryData::RPMN_carhorn_wav, BinaryData::RPMN_carhorn_wavSize),
        std::make_pair(BinaryData::RPMN_churchbells_wav, BinaryData::RPMN_churchbells_wavSize),
        std::make_pair(BinaryData::RPMN_ebass_wav, BinaryData::RPMN_ebass_wavSize),
        std::make_pair(BinaryData::RPMN_echobrass_wav, BinaryData::RPMN_echobrass_wavSize),
        std::make_pair(BinaryData::RPMN_emergencyalarm_wav, BinaryData::RPMN_emergencyalarm_wavSize),
        std::make_pair(BinaryData::RPMN_eorgan_wav, BinaryData::RPMN_eorgan_wavSize),
        std::make_pair(BinaryData::RPMN_flute_wav, BinaryData::RPMN_flute_wavSize),
        std::make_pair(BinaryData::RPMN_gamelan_wav, BinaryData::RPMN_gamelan_wavSize),
        std::make_pair(BinaryData::RPMN_metalguitar_wav, BinaryData::RPMN_metalguitar_wavSize),
        std::make_pair(BinaryData::RPMN_orchestrahit_wav, BinaryData::RPMN_orchestrahit_wavSize),
        std::make_pair(BinaryData::RPMN_piano_wav, BinaryData::RPMN_piano_wavSize),
        std::make_pair(BinaryData::RPMN_sitar_wav, BinaryData::RPMN_sitar_wavSize),
        std::make_pair(BinaryData::RPMN_synthlead_wav, BinaryData::RPMN_synthlead_wavSize),
        std::make_pair(BinaryData::RPMN_synthreed_wav, BinaryData::RPMN_synthreed_wavSize),
        std::make_pair(BinaryData::RPMN_twinkleecho_wav, BinaryData::RPMN_twinkleecho_wavSize),
        std::make_pair(BinaryData::RPMN_vibraphone_wav, BinaryData::RPMN_vibraphone_wavSize),
        std::make_pair(BinaryData::RPMN_vocoder_wav, BinaryData::RPMN_vocoder_wavSize),
        std::make_pair(BinaryData::RPMN_warmstrings_wav, BinaryData::RPMN_warmstrings_wavSize),
        std::make_pair(BinaryData::RPMN_wawvoice_wav, BinaryData::RPMN_wawvoice_wavSize)
    };
    
    std::pair<const char *, const int> CasioSa10[12] {
        std::make_pair(BinaryData::SA10_accordion_wav, BinaryData::SA10_accordion_wavSize),
        std::make_pair(BinaryData::SA10_bassoon_wav, BinaryData::SA10_bassoon_wavSize),
        std::make_pair(BinaryData::SA10_cello_wav, BinaryData::SA10_cello_wavSize),
        std::make_pair(BinaryData::SA10_epiano_wav, BinaryData::SA10_epiano_wavSize),
        std::make_pair(BinaryData::SA10_flute_wav, BinaryData::SA10_flute_wavSize),
        std::make_pair(BinaryData::SA10_honkypiano_wav, BinaryData::SA10_honkypiano_wavSize),
        std::make_pair(BinaryData::SA10_metalguitar_wav, BinaryData::SA10_metalguitar_wavSize),
        std::make_pair(BinaryData::SA10_piano_wav, BinaryData::SA10_piano_wavSize),
        std::make_pair(BinaryData::SA10_poplead_wav, BinaryData::SA10_poplead_wavSize),
        std::make_pair(BinaryData::SA10_synthaccordion_wav, BinaryData::SA10_synthaccordion_wavSize),
        std::make_pair(BinaryData::SA10_synthbrass_wav, BinaryData::SA10_synthbrass_wavSize),
        std::make_pair(BinaryData::SA10_synthlead_wav, BinaryData::SA10_synthlead_wavSize)
    };
    
    std::pair<const char *, const int> CasioSk1[8] {
        std::make_pair(BinaryData::SK1_brass_wav, BinaryData::SK1_brass_wavSize),
        std::make_pair(BinaryData::SK1_flute_wav, BinaryData::SK1_flute_wavSize),
        std::make_pair(BinaryData::SK1_organ_wav, BinaryData::SK1_organ_wavSize),
        std::make_pair(BinaryData::SK1_piano_wav, BinaryData::SK1_piano_wavSize),
        std::make_pair(BinaryData::SK1_pipeorgan_wav, BinaryData::SK1_pipeorgan_wavSize),
        std::make_pair(BinaryData::SK1_synthdrum_wav, BinaryData::SK1_synthdrum_wavSize),
        std::make_pair(BinaryData::SK1_trumpet_wav, BinaryData::SK1_trumpet_wavSize),
        std::make_pair(BinaryData::SK1_voice_wav, BinaryData::SK1_voice_wavSize)
    };
};
