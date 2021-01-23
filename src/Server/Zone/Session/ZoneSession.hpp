/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/
#ifndef HORIZON_ZONE_SESSION_ZONESESSION_HPP
#define HORIZON_ZONE_SESSION_ZONESESSION_HPP

#include "Core/Networking/Session.hpp"
#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Configuration/ServerConfiguration.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"

#include <memory>

#if CLIENT_TYPE == 'R'
#if PACKET_VERSION >= 20190109
#include "Server/Zone/Packets/RE/20190109.hpp"
#elif PACKET_VERSION >= 20181226
#include "Server/Zone/Packets/RE/20181226.hpp"
#elif PACKET_VERSION >= 20181219
#include "Server/Zone/Packets/RE/20181219.hpp"
#elif PACKET_VERSION >= 20181212
#include "Server/Zone/Packets/RE/20181212.hpp"
#elif PACKET_VERSION >= 20181205
#include "Server/Zone/Packets/RE/20181205.hpp"
#elif PACKET_VERSION >= 20181128
#include "Server/Zone/Packets/RE/20181128.hpp"
#elif PACKET_VERSION >= 20181121
#include "Server/Zone/Packets/RE/20181121.hpp"
#elif PACKET_VERSION >= 20181114
#include "Server/Zone/Packets/RE/20181114.hpp"
#elif PACKET_VERSION >= 20181107
#include "Server/Zone/Packets/RE/20181107.hpp"
#elif PACKET_VERSION >= 20181031
#include "Server/Zone/Packets/RE/20181031.hpp"
#elif PACKET_VERSION >= 20181017
#include "Server/Zone/Packets/RE/20181017.hpp"
#elif PACKET_VERSION >= 20181002
#include "Server/Zone/Packets/RE/20181002.hpp"
#elif PACKET_VERSION >= 20180919
#include "Server/Zone/Packets/RE/20180919.hpp"
#elif PACKET_VERSION >= 20180912
#include "Server/Zone/Packets/RE/20180912.hpp"
#elif PACKET_VERSION >= 20180829
#include "Server/Zone/Packets/RE/20180829.hpp"
#elif PACKET_VERSION >= 20180822
#include "Server/Zone/Packets/RE/20180822.hpp"
#elif PACKET_VERSION >= 20180808
#include "Server/Zone/Packets/RE/20180808.hpp"
#elif PACKET_VERSION >= 20180801
#include "Server/Zone/Packets/RE/20180801.hpp"
#elif PACKET_VERSION >= 20180718
#include "Server/Zone/Packets/RE/20180718.hpp"
#elif PACKET_VERSION >= 20180711
#include "Server/Zone/Packets/RE/20180711.hpp"
#elif PACKET_VERSION >= 20180704
#include "Server/Zone/Packets/RE/20180704.hpp"
#elif PACKET_VERSION >= 20180621
#include "Server/Zone/Packets/RE/20180621.hpp"
#elif PACKET_VERSION >= 20180620
#include "Server/Zone/Packets/RE/20180620.hpp"
#elif PACKET_VERSION >= 20180612
#include "Server/Zone/Packets/RE/20180612.hpp"
#elif PACKET_VERSION >= 20180605
#include "Server/Zone/Packets/RE/20180605.hpp"
#elif PACKET_VERSION >= 20180530
#include "Server/Zone/Packets/RE/20180530.hpp"
#elif PACKET_VERSION >= 20180523
#include "Server/Zone/Packets/RE/20180523.hpp"
#elif PACKET_VERSION >= 20180516
#include "Server/Zone/Packets/RE/20180516.hpp"
#elif PACKET_VERSION >= 20180502
#include "Server/Zone/Packets/RE/20180502.hpp"
#elif PACKET_VERSION >= 20180425
#include "Server/Zone/Packets/RE/20180425.hpp"
#elif PACKET_VERSION >= 20180418
#include "Server/Zone/Packets/RE/20180418.hpp"
#elif PACKET_VERSION >= 20180404
#include "Server/Zone/Packets/RE/20180404.hpp"
#elif PACKET_VERSION >= 20180328
#include "Server/Zone/Packets/RE/20180328.hpp"
#elif PACKET_VERSION >= 20180321
#include "Server/Zone/Packets/RE/20180321.hpp"
#elif PACKET_VERSION >= 20180307
#include "Server/Zone/Packets/RE/20180307.hpp"
#elif PACKET_VERSION >= 20180221
#include "Server/Zone/Packets/RE/20180221.hpp"
#elif PACKET_VERSION >= 20180213
#include "Server/Zone/Packets/RE/20180213.hpp"
#elif PACKET_VERSION >= 20180207
#include "Server/Zone/Packets/RE/20180207.hpp"
#elif PACKET_VERSION >= 20180124
#include "Server/Zone/Packets/RE/20180124.hpp"
#elif PACKET_VERSION >= 20180117
#include "Server/Zone/Packets/RE/20180117.hpp"
#elif PACKET_VERSION >= 20180103
#include "Server/Zone/Packets/RE/20180103.hpp"
#elif PACKET_VERSION >= 20171227
#include "Server/Zone/Packets/RE/20171227.hpp"
#elif PACKET_VERSION >= 20171220
#include "Server/Zone/Packets/RE/20171220.hpp"
#elif PACKET_VERSION >= 20171213
#include "Server/Zone/Packets/RE/20171213.hpp"
#elif PACKET_VERSION >= 20171206
#include "Server/Zone/Packets/RE/20171206.hpp"
#elif PACKET_VERSION >= 20171129
#include "Server/Zone/Packets/RE/20171129.hpp"
#elif PACKET_VERSION >= 20171122
#include "Server/Zone/Packets/RE/20171122.hpp"
#elif PACKET_VERSION >= 20171115
#include "Server/Zone/Packets/RE/20171115.hpp"
#elif PACKET_VERSION >= 20171108
#include "Server/Zone/Packets/RE/20171108.hpp"
#elif PACKET_VERSION >= 20171101
#include "Server/Zone/Packets/RE/20171101.hpp"
#elif PACKET_VERSION >= 20171025
#include "Server/Zone/Packets/RE/20171025.hpp"
#elif PACKET_VERSION >= 20171018
#include "Server/Zone/Packets/RE/20171018.hpp"
#elif PACKET_VERSION >= 20171011
#include "Server/Zone/Packets/RE/20171011.hpp"
#elif PACKET_VERSION >= 20171002
#include "Server/Zone/Packets/RE/20171002.hpp"
#elif PACKET_VERSION >= 20170927
#include "Server/Zone/Packets/RE/20170927.hpp"
#elif PACKET_VERSION >= 20170920
#include "Server/Zone/Packets/RE/20170920.hpp"
#elif PACKET_VERSION >= 20170913
#include "Server/Zone/Packets/RE/20170913.hpp"
#elif PACKET_VERSION >= 20170906
#include "Server/Zone/Packets/RE/20170906.hpp"
#elif PACKET_VERSION >= 20170830
#include "Server/Zone/Packets/RE/20170830.hpp"
#elif PACKET_VERSION >= 20170823
#include "Server/Zone/Packets/RE/20170823.hpp"
#elif PACKET_VERSION >= 20170816
#include "Server/Zone/Packets/RE/20170816.hpp"
#elif PACKET_VERSION >= 20170809
#include "Server/Zone/Packets/RE/20170809.hpp"
#elif PACKET_VERSION >= 20170801
#include "Server/Zone/Packets/RE/20170801.hpp"
#elif PACKET_VERSION >= 20170726
#include "Server/Zone/Packets/RE/20170726.hpp"
#elif PACKET_VERSION >= 20170719
#include "Server/Zone/Packets/RE/20170719.hpp"
#elif PACKET_VERSION >= 20170712
#include "Server/Zone/Packets/RE/20170712.hpp"
#elif PACKET_VERSION >= 20170705
#include "Server/Zone/Packets/RE/20170705.hpp"
#elif PACKET_VERSION >= 20170628
#include "Server/Zone/Packets/RE/20170628.hpp"
#elif PACKET_VERSION >= 20170621
#include "Server/Zone/Packets/RE/20170621.hpp"
#elif PACKET_VERSION >= 20170614
#include "Server/Zone/Packets/RE/20170614.hpp"
#elif PACKET_VERSION >= 20170607
#include "Server/Zone/Packets/RE/20170607.hpp"
#elif PACKET_VERSION >= 20170531
#include "Server/Zone/Packets/RE/20170531.hpp"
#elif PACKET_VERSION >= 20170524
#include "Server/Zone/Packets/RE/20170524.hpp"
#elif PACKET_VERSION >= 20170517
#include "Server/Zone/Packets/RE/20170517.hpp"
#elif PACKET_VERSION >= 20170502
#include "Server/Zone/Packets/RE/20170502.hpp"
#elif PACKET_VERSION >= 20170426
#include "Server/Zone/Packets/RE/20170426.hpp"
#elif PACKET_VERSION >= 20170419
#include "Server/Zone/Packets/RE/20170419.hpp"
#elif PACKET_VERSION >= 20170412
#include "Server/Zone/Packets/RE/20170412.hpp"
#elif PACKET_VERSION >= 20170405
#include "Server/Zone/Packets/RE/20170405.hpp"
#elif PACKET_VERSION >= 20170329
#include "Server/Zone/Packets/RE/20170329.hpp"
#elif PACKET_VERSION >= 20170322
#include "Server/Zone/Packets/RE/20170322.hpp"
#elif PACKET_VERSION >= 20170315
#include "Server/Zone/Packets/RE/20170315.hpp"
#elif PACKET_VERSION >= 20170308
#include "Server/Zone/Packets/RE/20170308.hpp"
#elif PACKET_VERSION >= 20170228
#include "Server/Zone/Packets/RE/20170228.hpp"
#elif PACKET_VERSION >= 20170222
#include "Server/Zone/Packets/RE/20170222.hpp"
#elif PACKET_VERSION >= 20170215
#include "Server/Zone/Packets/RE/20170215.hpp"
#elif PACKET_VERSION >= 20170208
#include "Server/Zone/Packets/RE/20170208.hpp"
#else
#include "Server/Zone/Packets/RE/Default.hpp"
#endif
#elif CLIENT_TYPE == 'Z'
#if PACKET_VERSION >= 20181226
#include "Server/Zone/Packets/Zero/20181226.hpp"
#elif PACKET_VERSION >= 20181219
#include "Server/Zone/Packets/Zero/20181219.hpp"
#elif PACKET_VERSION >= 20181212
#include "Server/Zone/Packets/Zero/20181212.hpp"
#elif PACKET_VERSION >= 20181128
#include "Server/Zone/Packets/Zero/20181128.hpp"
#elif PACKET_VERSION >= 20181120
#include "Server/Zone/Packets/Zero/20181120.hpp"
#elif PACKET_VERSION >= 20181114
#include "Server/Zone/Packets/Zero/20181114.hpp"
#elif PACKET_VERSION >= 20181024
#include "Server/Zone/Packets/Zero/20181024.hpp"
#elif PACKET_VERSION >= 20181010
#include "Server/Zone/Packets/Zero/20181010.hpp"
#elif PACKET_VERSION >= 20180928
#include "Server/Zone/Packets/Zero/20180928.hpp"
#elif PACKET_VERSION >= 20180919
#include "Server/Zone/Packets/Zero/20180919.hpp"
#elif PACKET_VERSION >= 20180912
#include "Server/Zone/Packets/Zero/20180912.hpp"
#elif PACKET_VERSION >= 20180905
#include "Server/Zone/Packets/Zero/20180905.hpp"
#elif PACKET_VERSION >= 20180829
#include "Server/Zone/Packets/Zero/20180829.hpp"
#elif PACKET_VERSION >= 20180822
#include "Server/Zone/Packets/Zero/20180822.hpp"
#elif PACKET_VERSION >= 20180808
#include "Server/Zone/Packets/Zero/20180808.hpp"
#elif PACKET_VERSION >= 20180801
#include "Server/Zone/Packets/Zero/20180801.hpp"
#elif PACKET_VERSION >= 20180725
#include "Server/Zone/Packets/Zero/20180725.hpp"
#elif PACKET_VERSION >= 20180711
#include "Server/Zone/Packets/Zero/20180711.hpp"
#elif PACKET_VERSION >= 20180703
#include "Server/Zone/Packets/Zero/20180703.hpp"
#elif PACKET_VERSION >= 20180627
#include "Server/Zone/Packets/Zero/20180627.hpp"
#elif PACKET_VERSION >= 20180605
#include "Server/Zone/Packets/Zero/20180605.hpp"
#elif PACKET_VERSION >= 20180523
#include "Server/Zone/Packets/Zero/20180523.hpp"
#elif PACKET_VERSION >= 20180511
#include "Server/Zone/Packets/Zero/20180511.hpp"
#elif PACKET_VERSION >= 20180509
#include "Server/Zone/Packets/Zero/20180509.hpp"
#elif PACKET_VERSION >= 20180425
#include "Server/Zone/Packets/Zero/20180425.hpp"
#elif PACKET_VERSION >= 20180411
#include "Server/Zone/Packets/Zero/20180411.hpp"
#elif PACKET_VERSION >= 20180328
#include "Server/Zone/Packets/Zero/20180328.hpp"
#elif PACKET_VERSION >= 20180321
#include "Server/Zone/Packets/Zero/20180321.hpp"
#elif PACKET_VERSION >= 20180315
#include "Server/Zone/Packets/Zero/20180315.hpp"
#elif PACKET_VERSION >= 20180314
#include "Server/Zone/Packets/Zero/20180314.hpp"
#elif PACKET_VERSION >= 20180309
#include "Server/Zone/Packets/Zero/20180309.hpp"
#elif PACKET_VERSION >= 20180307
#include "Server/Zone/Packets/Zero/20180307.hpp"
#elif PACKET_VERSION >= 20180228
#include "Server/Zone/Packets/Zero/20180228.hpp"
#elif PACKET_VERSION >= 20180221
#include "Server/Zone/Packets/Zero/20180221.hpp"
#elif PACKET_VERSION >= 20180213
#include "Server/Zone/Packets/Zero/20180213.hpp"
#elif PACKET_VERSION >= 20180207
#include "Server/Zone/Packets/Zero/20180207.hpp"
#elif PACKET_VERSION >= 20180131
#include "Server/Zone/Packets/Zero/20180131.hpp"
#elif PACKET_VERSION >= 20180117
#include "Server/Zone/Packets/Zero/20180117.hpp"
#elif PACKET_VERSION >= 20180103
#include "Server/Zone/Packets/Zero/20180103.hpp"
#elif PACKET_VERSION >= 20171229
#include "Server/Zone/Packets/Zero/20171229.hpp"
#elif PACKET_VERSION >= 20171227
#include "Server/Zone/Packets/Zero/20171227.hpp"
#elif PACKET_VERSION >= 20171221
#include "Server/Zone/Packets/Zero/20171221.hpp"
#elif PACKET_VERSION >= 20171220
#include "Server/Zone/Packets/Zero/20171220.hpp"
#elif PACKET_VERSION >= 20171214
#include "Server/Zone/Packets/Zero/20171214.hpp"
#elif PACKET_VERSION >= 20171213
#include "Server/Zone/Packets/Zero/20171213.hpp"
#elif PACKET_VERSION >= 20171212
#include "Server/Zone/Packets/Zero/20171212.hpp"
#elif PACKET_VERSION >= 20171211
#include "Server/Zone/Packets/Zero/20171211.hpp"
#elif PACKET_VERSION >= 20171210
#include "Server/Zone/Packets/Zero/20171210.hpp"
#elif PACKET_VERSION >= 20171209
#include "Server/Zone/Packets/Zero/20171209.hpp"
#elif PACKET_VERSION >= 20171208
#include "Server/Zone/Packets/Zero/20171208.hpp"
#elif PACKET_VERSION >= 20171206
#include "Server/Zone/Packets/Zero/20171206.hpp"
#elif PACKET_VERSION >= 20171204
#include "Server/Zone/Packets/Zero/20171204.hpp"
#elif PACKET_VERSION >= 20171130
#include "Server/Zone/Packets/Zero/20171130.hpp"
#elif PACKET_VERSION >= 20171128
#include "Server/Zone/Packets/Zero/20171128.hpp"
#elif PACKET_VERSION >= 20171127
#include "Server/Zone/Packets/Zero/20171127.hpp"
#elif PACKET_VERSION >= 20171123
#include "Server/Zone/Packets/Zero/20171123.hpp"
#elif PACKET_VERSION >= 20171122
#include "Server/Zone/Packets/Zero/20171122.hpp"
#elif PACKET_VERSION >= 20171121
#include "Server/Zone/Packets/Zero/20171121.hpp"
#elif PACKET_VERSION >= 20171117
#include "Server/Zone/Packets/Zero/20171117.hpp"
#elif PACKET_VERSION >= 20171116
#include "Server/Zone/Packets/Zero/20171116.hpp"
#elif PACKET_VERSION >= 20171115
#include "Server/Zone/Packets/Zero/20171115.hpp"
#elif PACKET_VERSION >= 20171113
#include "Server/Zone/Packets/Zero/20171113.hpp"
#elif PACKET_VERSION >= 20171109
#include "Server/Zone/Packets/Zero/20171109.hpp"
#elif PACKET_VERSION >= 20171031
#include "Server/Zone/Packets/Zero/20171031.hpp"
#elif PACKET_VERSION >= 20171030
#include "Server/Zone/Packets/Zero/20171030.hpp"
#elif PACKET_VERSION >= 20171027
#include "Server/Zone/Packets/Zero/20171027.hpp"
#elif PACKET_VERSION >= 20171025
#include "Server/Zone/Packets/Zero/20171025.hpp"
#elif PACKET_VERSION >= 20171024
#include "Server/Zone/Packets/Zero/20171024.hpp"
#elif PACKET_VERSION >= 20171023
#include "Server/Zone/Packets/Zero/20171023.hpp"
#elif PACKET_VERSION >= 20171019
#include "Server/Zone/Packets/Zero/20171019.hpp"
#elif PACKET_VERSION >= 20171018
#include "Server/Zone/Packets/Zero/20171018.hpp"
#else
#include "Server/Zone/Packets/Zero/Default.hpp"
#endif
#elif CLIENT_TYPE == 'M'
#if PACKET_VERSION >= 20190109
#include "Server/Zone/Packets/Ragexe/20190109.hpp"
#elif PACKET_VERSION >= 20181226
#include "Server/Zone/Packets/Ragexe/20181226.hpp"
#elif PACKET_VERSION >= 20181219
#include "Server/Zone/Packets/Ragexe/20181219.hpp"
#elif PACKET_VERSION >= 20181212
#include "Server/Zone/Packets/Ragexe/20181212.hpp"
#elif PACKET_VERSION >= 20181205
#include "Server/Zone/Packets/Ragexe/20181205.hpp"
#elif PACKET_VERSION >= 20181128
#include "Server/Zone/Packets/Ragexe/20181128.hpp"
#elif PACKET_VERSION >= 20181121
#include "Server/Zone/Packets/Ragexe/20181121.hpp"
#elif PACKET_VERSION >= 20181114
#include "Server/Zone/Packets/Ragexe/20181114.hpp"
#elif PACKET_VERSION >= 20181107
#include "Server/Zone/Packets/Ragexe/20181107.hpp"
#elif PACKET_VERSION >= 20181031
#include "Server/Zone/Packets/Ragexe/20181031.hpp"
#elif PACKET_VERSION >= 20181024
#include "Server/Zone/Packets/Ragexe/20181024.hpp"
#elif PACKET_VERSION >= 20181017
#include "Server/Zone/Packets/Ragexe/20181017.hpp"
#elif PACKET_VERSION >= 20181002
#include "Server/Zone/Packets/Ragexe/20181002.hpp"
#elif PACKET_VERSION >= 20180919
#include "Server/Zone/Packets/Ragexe/20180919.hpp"
#elif PACKET_VERSION >= 20180912
#include "Server/Zone/Packets/Ragexe/20180912.hpp"
#elif PACKET_VERSION >= 20180831
#include "Server/Zone/Packets/Ragexe/20180831.hpp"
#elif PACKET_VERSION >= 20180829
#include "Server/Zone/Packets/Ragexe/20180829.hpp"
#elif PACKET_VERSION >= 20180822
#include "Server/Zone/Packets/Ragexe/20180822.hpp"
#elif PACKET_VERSION >= 20180808
#include "Server/Zone/Packets/Ragexe/20180808.hpp"
#elif PACKET_VERSION >= 20180801
#include "Server/Zone/Packets/Ragexe/20180801.hpp"
#elif PACKET_VERSION >= 20180718
#include "Server/Zone/Packets/Ragexe/20180718.hpp"
#elif PACKET_VERSION >= 20180704
#include "Server/Zone/Packets/Ragexe/20180704.hpp"
#elif PACKET_VERSION >= 20180621
#include "Server/Zone/Packets/Ragexe/20180621.hpp"
#elif PACKET_VERSION >= 20180620
#include "Server/Zone/Packets/Ragexe/20180620.hpp"
#elif PACKET_VERSION >= 20180605
#include "Server/Zone/Packets/Ragexe/20180605.hpp"
#elif PACKET_VERSION >= 20180530
#include "Server/Zone/Packets/Ragexe/20180530.hpp"
#elif PACKET_VERSION >= 20180523
#include "Server/Zone/Packets/Ragexe/20180523.hpp"
#elif PACKET_VERSION >= 20180516
#include "Server/Zone/Packets/Ragexe/20180516.hpp"
#elif PACKET_VERSION >= 20180509
#include "Server/Zone/Packets/Ragexe/20180509.hpp"
#elif PACKET_VERSION >= 20180502
#include "Server/Zone/Packets/Ragexe/20180502.hpp"
#elif PACKET_VERSION >= 20180425
#include "Server/Zone/Packets/Ragexe/20180425.hpp"
#elif PACKET_VERSION >= 20180418
#include "Server/Zone/Packets/Ragexe/20180418.hpp"
#elif PACKET_VERSION >= 20180404
#include "Server/Zone/Packets/Ragexe/20180404.hpp"
#elif PACKET_VERSION >= 20180328
#include "Server/Zone/Packets/Ragexe/20180328.hpp"
#elif PACKET_VERSION >= 20180321
#include "Server/Zone/Packets/Ragexe/20180321.hpp"
#elif PACKET_VERSION >= 20180315
#include "Server/Zone/Packets/Ragexe/20180315.hpp"
#elif PACKET_VERSION >= 20180314
#include "Server/Zone/Packets/Ragexe/20180314.hpp"
#elif PACKET_VERSION >= 20180309
#include "Server/Zone/Packets/Ragexe/20180309.hpp"
#elif PACKET_VERSION >= 20180307
#include "Server/Zone/Packets/Ragexe/20180307.hpp"
#elif PACKET_VERSION >= 20180221
#include "Server/Zone/Packets/Ragexe/20180221.hpp"
#elif PACKET_VERSION >= 20180213
#include "Server/Zone/Packets/Ragexe/20180213.hpp"
#elif PACKET_VERSION >= 20180207
#include "Server/Zone/Packets/Ragexe/20180207.hpp"
#elif PACKET_VERSION >= 20180131
#include "Server/Zone/Packets/Ragexe/20180131.hpp"
#elif PACKET_VERSION >= 20180124
#include "Server/Zone/Packets/Ragexe/20180124.hpp"
#elif PACKET_VERSION >= 20180117
#include "Server/Zone/Packets/Ragexe/20180117.hpp"
#elif PACKET_VERSION >= 20180103
#include "Server/Zone/Packets/Ragexe/20180103.hpp"
#elif PACKET_VERSION >= 20171227
#include "Server/Zone/Packets/Ragexe/20171227.hpp"
#elif PACKET_VERSION >= 20171220
#include "Server/Zone/Packets/Ragexe/20171220.hpp"
#elif PACKET_VERSION >= 20171213
#include "Server/Zone/Packets/Ragexe/20171213.hpp"
#elif PACKET_VERSION >= 20171206
#include "Server/Zone/Packets/Ragexe/20171206.hpp"
#elif PACKET_VERSION >= 20171129
#include "Server/Zone/Packets/Ragexe/20171129.hpp"
#elif PACKET_VERSION >= 20171122
#include "Server/Zone/Packets/Ragexe/20171122.hpp"
#elif PACKET_VERSION >= 20171115
#include "Server/Zone/Packets/Ragexe/20171115.hpp"
#elif PACKET_VERSION >= 20171108
#include "Server/Zone/Packets/Ragexe/20171108.hpp"
#elif PACKET_VERSION >= 20171101
#include "Server/Zone/Packets/Ragexe/20171101.hpp"
#elif PACKET_VERSION >= 20171025
#include "Server/Zone/Packets/Ragexe/20171025.hpp"
#elif PACKET_VERSION >= 20171018
#include "Server/Zone/Packets/Ragexe/20171018.hpp"
#elif PACKET_VERSION >= 20171011
#include "Server/Zone/Packets/Ragexe/20171011.hpp"
#elif PACKET_VERSION >= 20171002
#include "Server/Zone/Packets/Ragexe/20171002.hpp"
#elif PACKET_VERSION >= 20170927
#include "Server/Zone/Packets/Ragexe/20170927.hpp"
#elif PACKET_VERSION >= 20170920
#include "Server/Zone/Packets/Ragexe/20170920.hpp"
#elif PACKET_VERSION >= 20170913
#include "Server/Zone/Packets/Ragexe/20170913.hpp"
#elif PACKET_VERSION >= 20170906
#include "Server/Zone/Packets/Ragexe/20170906.hpp"
#elif PACKET_VERSION >= 20170830
#include "Server/Zone/Packets/Ragexe/20170830.hpp"
#elif PACKET_VERSION >= 20170823
#include "Server/Zone/Packets/Ragexe/20170823.hpp"
#elif PACKET_VERSION >= 20170816
#include "Server/Zone/Packets/Ragexe/20170816.hpp"
#elif PACKET_VERSION >= 20170809
#include "Server/Zone/Packets/Ragexe/20170809.hpp"
#elif PACKET_VERSION >= 20170801
#include "Server/Zone/Packets/Ragexe/20170801.hpp"
#elif PACKET_VERSION >= 20170726
#include "Server/Zone/Packets/Ragexe/20170726.hpp"
#elif PACKET_VERSION >= 20170719
#include "Server/Zone/Packets/Ragexe/20170719.hpp"
#elif PACKET_VERSION >= 20170712
#include "Server/Zone/Packets/Ragexe/20170712.hpp"
#elif PACKET_VERSION >= 20170705
#include "Server/Zone/Packets/Ragexe/20170705.hpp"
#elif PACKET_VERSION >= 20170628
#include "Server/Zone/Packets/Ragexe/20170628.hpp"
#elif PACKET_VERSION >= 20170621
#include "Server/Zone/Packets/Ragexe/20170621.hpp"
#elif PACKET_VERSION >= 20170614
#include "Server/Zone/Packets/Ragexe/20170614.hpp"
#elif PACKET_VERSION >= 20170607
#include "Server/Zone/Packets/Ragexe/20170607.hpp"
#elif PACKET_VERSION >= 20170531
#include "Server/Zone/Packets/Ragexe/20170531.hpp"
#elif PACKET_VERSION >= 20170524
#include "Server/Zone/Packets/Ragexe/20170524.hpp"
#elif PACKET_VERSION >= 20170517
#include "Server/Zone/Packets/Ragexe/20170517.hpp"
#elif PACKET_VERSION >= 20170502
#include "Server/Zone/Packets/Ragexe/20170502.hpp"
#elif PACKET_VERSION >= 20170426
#include "Server/Zone/Packets/Ragexe/20170426.hpp"
#elif PACKET_VERSION >= 20170419
#include "Server/Zone/Packets/Ragexe/20170419.hpp"
#elif PACKET_VERSION >= 20170412
#include "Server/Zone/Packets/Ragexe/20170412.hpp"
#elif PACKET_VERSION >= 20170405
#include "Server/Zone/Packets/Ragexe/20170405.hpp"
#elif PACKET_VERSION >= 20170329
#include "Server/Zone/Packets/Ragexe/20170329.hpp"
#elif PACKET_VERSION >= 20170322
#include "Server/Zone/Packets/Ragexe/20170322.hpp"
#elif PACKET_VERSION >= 20170315
#include "Server/Zone/Packets/Ragexe/20170315.hpp"
#elif PACKET_VERSION >= 20170308
#include "Server/Zone/Packets/Ragexe/20170308.hpp"
#elif PACKET_VERSION >= 20170228
#include "Server/Zone/Packets/Ragexe/20170228.hpp"
#elif PACKET_VERSION >= 20170222
#include "Server/Zone/Packets/Ragexe/20170222.hpp"
#elif PACKET_VERSION >= 20170215
#include "Server/Zone/Packets/Ragexe/20170215.hpp"
#elif PACKET_VERSION >= 20170208
#include "Server/Zone/Packets/Ragexe/20170208.hpp"
#elif PACKET_VERSION >= 20170201
#include "Server/Zone/Packets/Ragexe/20170201.hpp"
#elif PACKET_VERSION >= 20170125
#include "Server/Zone/Packets/Ragexe/20170125.hpp"
#elif PACKET_VERSION >= 20170118
#include "Server/Zone/Packets/Ragexe/20170118.hpp"
#elif PACKET_VERSION >= 20170111
#include "Server/Zone/Packets/Ragexe/20170111.hpp"
#elif PACKET_VERSION >= 20170104
#include "Server/Zone/Packets/Ragexe/20170104.hpp"
#else
#include "Server/Zone/Packets/Ragexe/Default.hpp"
#endif
#endif

namespace Horizon
{
namespace Zone
{
class ZoneSocket;
class ZoneSession : public Horizon::Networking::Session<ZoneSocket, ZoneSession>
{
public:
	ZoneSession(std::shared_ptr<ZoneSocket> socket);
	~ZoneSession();

	void transmit_buffer(ByteBuffer _buffer, std::size_t size);

	void update(uint32_t diff);

	void perform_cleanup();

	void initialize();
	
	std::unique_ptr<ZoneClientInterface> &clif() { return _clif; }
	std::unique_ptr<ClientPacketLengthTable> &pkt_tbl() { return _pkt_tbl; }
	std::shared_ptr<Entities::Player> player() { return _player.expired() ? nullptr : _player.lock(); }
	void set_player(std::shared_ptr<Entities::Player> pl) { _player = pl; }

protected:
	std::unique_ptr<ZoneClientInterface> _clif;
	std::unique_ptr<ClientPacketLengthTable> _pkt_tbl;
	std::weak_ptr<Entities::Player> _player;
};
}
}

#endif
