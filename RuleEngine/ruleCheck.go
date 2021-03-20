/*
 * @Author: your name
 * @Date: 2021-01-11 13:38:04
 * @LastEditTime: 2021-01-12 19:22:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /C-Study/ruleCheck.go
 */

package main

import (
	"fmt"
	"regexp"
	"strings"
)

var orderLogInfo string

var orderRuleExp string

var driverLogInfo string

// var driverInfoMap map[string]string
var driverRuleExp string

func setInfo() {
	orderLogInfo = `[INFO][2021-01-11T11:07:46.171+0800][src/RuleEngineHandler.cpp:1537] _com_request_out||traceid=0ab729ce5ffbc10200000498041520dd||REQ=Y||order_id=35238474623751||timestamp=1610334466133529392||hintCode=0||offset=0||sid=||appid=301||ab_fps_rule_offline_test=0||airport_code=||airport_id=0||anycar_type=2||apiOrderTag=0,0||apollo_label_group=||apollo_label_group_for_call_passenger=||area=1||area_toarea=1,1||arr_dynamic_price=[]||auto_trigger=0||ban=0||blind_type=0||booking_assign=0||bubble_trace_id=ac161d0e5ffbc0fe7e09524710da0a03||callCount=0||callcar_passenger_phone=15510831780||canonical_country_code=CN||cap_price=0||car_pool=0||carpool_type=||channel=102||cnt_call=1763||combo_distance=0||combo_fee=0||combo_id=0||combo_time=0||combo_type=0||commercial_driver_tag=0||confirm_walk_type=0||contract=0||county_id=110114||createTime=2021-01-11 11:07:45||current_lat=40.043805338542||current_lng=116.28952582465||cyborg_sub_id=3070110071336||day_of_week=1||departure_time=2021-01-11 11:07:45||dest_lat=40.120926||dest_lng=116.759332||dest_name=顺义|南彩村鲍淑英服装加工部||dest_poi_id=1023339540573585408||dest_tag=0||disability_type=0||dispatch_type=0||district=010||double_income=0||driver_id=0||driver_info_fee=0||driver_info_fee_without_discount=0||driver_is_filter=0||drunk_predict_value=0.156890||duse-fence-info={"from_114":[46952],"from_135":[209846],"from_214":[52658,51534,51536,51518],"from_22":[382921,525939,186256,381425,330718,197220,15535,1725,186228,526231,284922,5573,525947,74120,2787844,268332,364341,2429,89488,7769,89524,7865,200752,526181,389945,525507,72860,50480,65158,643326,193104,536041,499015,9017,210610,2349,3000324,525797,525941,327546,71308,192720,364333,96698,97300,15631,17733,3803323,194882,211978,526235,525943,485289,98776,368487,756780,376523,525599,526185,236142,373583,526183,237428,72656,2271,89540,523615,1286910,14955,526187,98774,181816,526391,71340,72688,719,46938,526397,327512,391887,18157,17083,237430,490291,361469,364349,7791,485201,1869242,98576,485199,72686,97204,170466,373585,9789,48562,237434,757102,93716,525509,237432,1073956,361465,209580,52722,568448,330682,71342,51598,15755,525945,525937,330676,361361,364337,93846,284982,525505,178936,279230,526313,46936,17967,232278,525535,1286904,382915,485001,195448,482997,103852,80868],"from_26":[489241,362947],"to_26":[223850]}||dynamic_kind=0||dynamic_price_info={"1100":{"dynamic_price":0,"dynamic":0,"is_hit_dynamic_capping":false,"is_hit_member_capping":false,"is_has_dynamic":0,"dynamic_type":0,"arrive_time":0,"rank_probability":0,"if_use_times":0,"dynamic_times":0,"dynamic_price_id":"","dynamic_discount_id":0,"dynamic_discount":0,"dynamic_kind":0,"near_driver_num":0,"near_order_num":0,"avg_driver_start_distance":0,"place":0,"wait_discount":0,"wait_minute":0,"car_level":1100,"order_type":0,"start_dest_distance":"53.772","start_dest_time":64}}||dynamic_type=0||dynamic_version=0||emergency_service_type=0||estimate_carpool_open=0||estimate_end_time=2021-01-11 12:11:45||estimate_fee=180||estimate_info={"estimate_id":"4f7b1df076bc618d1aa4b1fd5105f2fd","start_dest_distance":53772,"start_dest_time":64,"red_packet":0}||ether_predict_value=0.197298||expire_time=600||extra_info=||extra_type=49664||filter_drivers=[563888459354113,5147167,5877066]||forecast_time=64||fps_bubble_order=0||fps_skyeye_v2_close=1||fps_skyeye_v3_open=0||full_order_id=577305222746155783||gizzle_skyeye_passenger_basic={"p_gender": "-1", "age_level": "5"}||gov_order_mark=||grid_designated_num=476||grid_designated_week_hour_num=0||group_key=11_1100_0||head_url=||hitAreas=588598,3526365,3709480,187530,2740926,319562,262780,61860,3649409,541329,201744,3592981,3525653,61864,2740916,3724391,263480,2844714,222128,62510,2702108,623974,3519883,283388,3865872,316180,3873318,1052758,836282,1871212,488087,2560460,3782747,3865126,45564,330902,513707,233134,1173600,61038,563460,3677326,580862,318770,12237,371751,368377,3817044,756364,316186,1173596,579946,1163138,3875082,2022800,488385,2720868,108658,62516,362903,3813367,367295,1194810,593642,371289,1173602,579928,627752,3855405,3866814,2600258,1194788,317050,59680,374567,519619,591606,824666,1194798,2118248,316182,1699782,191684,3867935,696162,568440,999722,3560449,3870673,62514,3810481,1288166,2612066,1073020,1194784,1162258,329504,823760,279654,383237,3834863,279668,580924,1175038,2612068,3851902,107874,3868638,3816149,1162270,89886,696190,836280,561770,383261,97516,1194774,178488,3817043,3856228,1194806,366707,824340,3872404,1194778,623968,74936,316184,1053274,1194802,2438726,575680,999724,3692952,632954,590152,283204,3024356,1173608,1194762,93912,316310,44900,822424,3815057,2691018,1194792,1047558,580874,1175036,3854395,3649366,2524442,107872,3810482,3000325,3000327,1699784,3815058,2627370,3853573,1162264,580888,371753,824342,582188,508711,482203,400265,1173604,1108538,582064,260820,1194760,3689093,2600338,47254,3854587,3689087,826364,62512,197886,3851901,1765064,572560,3816150,311482,47998,3854586,2600252,312550,206552,2560466,3813368,3560477,1871660,84378,100290,1175040,401027,3818906,755076,1194766,3853572,3834864,3856229,587656,3868639,1052760,2063814,80062,482247,3852864,362949,72866,3686789,1194796,404213,2560464,3872405,279652,74938,1047560,286366,2723682,580886,1194780,366711,327782,722808,147406,660094,3046378,482323,1175032,1996310,1194770,836396,3836538,580884,3865125,97204,364341,178936,361361,193104,526235,93716,361469,71308,1869242,364337,284922,330676,525505,15631,526231,526391,368487,72656,1286910,98776,525939,7791,72860,237430,526183,526397,382921,757102,197220,526187,525797,526185,525941,89540,482997,268332,1286904,15535,46936,89488,376523,195448,499015,98774,48562,211978,364333,3803323,46938,330718,5573,382915,17967,18157,89524,568448,391887,373585,7769,1725,200752,389945,756780,361465,65158,52722,525937,279230,170466,209580,2787844,103852,186256,364349,96698,2429,17733,237428,284982,50480,643326,186228,97300,490291,74120,3000324,525599,7865,485201,9789,330682,14955,236142,210610,327512,373583,485199,192720,525943,71340,719,51598,237434,237432,1073956,525509,232278,381425,71342,72686,15755,2349,93846,525945,327546,526313,523615,525947,526181,194882,98576,181816,17083,485001,536041,72688,9017,525507,525535,2271,80868,485289,1457200,133910,529897,1457198,3526365,3709480,541329,186326,187534,184548,3525653,330902,3677326,1286906,366707,722808,3519883,71132,5181,74936,364345,283204,523455,72866,579928,2438726,1072606,3782747,147406,72738,404213,367295,83082,286368,56392,3836738,508711,1871212,374567,80062,89886,279200,2673036,1108550,47254,45564,402861,758122,186228,62466,72656,196306,236142,195446,89540,80868,364337,536041,192720,197230,74122,200752,200974,186256,368581,330682,89488,382921,1869242,268330,2279,499015,71308,193104,364745,89524,94154,365055,9789,2774916,147864,5573,1286908,103852,284974,7791,330718,330676,7865,72860,143918,2349,197218,267982,197402,1457200,529897,1457198,1101007,1101005,1101002,1101008||hit_dest_region=3526365,3709480,541329,186326,187534,184548,3525653,330902,3677326,1286906,366707,722808,3519883,71132,5181,74936,364345,283204,523455,72866,579928,2438726,1072606,3782747,147406,72738,404213,367295,83082,286368,56392,3836738,508711,1871212,374567,80062,89886,279200,2673036,1108550,47254,45564,402861,758122,186228,62466,72656,196306,236142,195446,89540,80868,364337,536041,192720,197230,74122,200752,200974,186256,368581,330682,89488,382921,1869242,268330,2279,499015,71308,193104,364745,89524,94154,365055,9789,2774916,147864,5573,1286908,103852,284974,7791,330718,330676,7865,72860,143918,2349,197218,267982,197402,1457200,529897,1457198||hit_route=1101007,1101005,1101002,1101008||hit_start_region=588598,3526365,3709480,187530,2740926,319562,262780,61860,3649409,541329,201744,3592981,3525653,61864,2740916,3724391,263480,2844714,222128,62510,2702108,623974,3519883,283388,3865872,316180,3873318,1052758,836282,1871212,488087,2560460,3782747,3865126,45564,330902,513707,233134,1173600,61038,563460,3677326,580862,318770,12237,371751,368377,3817044,756364,316186,1173596,579946,1163138,3875082,2022800,488385,2720868,108658,62516,362903,3813367,367295,1194810,593642,371289,1173602,579928,627752,3855405,3866814,2600258,1194788,317050,59680,374567,519619,591606,824666,1194798,2118248,316182,1699782,191684,3867935,696162,568440,999722,3560449,3870673,62514,3810481,1288166,2612066,1073020,1194784,1162258,329504,823760,279654,383237,3834863,279668,580924,1175038,2612068,3851902,107874,3868638,3816149,1162270,89886,696190,836280,561770,383261,97516,1194774,178488,3817043,3856228,1194806,366707,824340,3872404,1194778,623968,74936,316184,1053274,1194802,2438726,575680,999724,3692952,632954,590152,283204,3024356,1173608,1194762,93912,316310,44900,822424,3815057,2691018,1194792,1047558,580874,1175036,3854395,3649366,2524442,107872,3810482,3000325,3000327,1699784,3815058,2627370,3853573,1162264,580888,371753,824342,582188,508711,482203,400265,1173604,1108538,582064,260820,1194760,3689093,2600338,47254,3854587,3689087,826364,62512,197886,3851901,1765064,572560,3816150,311482,47998,3854586,2600252,312550,206552,2560466,3813368,3560477,1871660,84378,100290,1175040,401027,3818906,755076,1194766,3853572,3834864,3856229,587656,3868639,1052760,2063814,80062,482247,3852864,362949,72866,3686789,1194796,404213,2560464,3872405,279652,74938,1047560,286366,2723682,580886,1194780,366711,327782,722808,147406,660094,3046378,482323,1175032,1996310,1194770,836396,3836538,580884,3865125,97204,364341,178936,361361,193104,526235,93716,361469,71308,1869242,364337,284922,330676,525505,15631,526231,526391,368487,72656,1286910,98776,525939,7791,72860,237430,526183,526397,382921,757102,197220,526187,525797,526185,525941,89540,482997,268332,1286904,15535,46936,89488,376523,195448,499015,98774,48562,211978,364333,3803323,46938,330718,5573,382915,17967,18157,89524,568448,391887,373585,7769,1725,200752,389945,756780,361465,65158,52722,525937,279230,170466,209580,2787844,103852,186256,364349,96698,2429,17733,237428,284982,50480,643326,186228,97300,490291,74120,3000324,525599,7865,485201,9789,330682,14955,236142,210610,327512,373583,485199,192720,525943,71340,719,51598,237434,237432,1073956,525509,232278,381425,71342,72686,15755,2349,93846,525945,327546,526313,523615,525947,526181,194882,98576,181816,17083,485001,536041,72688,9017,525507,525535,2271,80868,485289,1457200,133910,529897,1457198||is_all_assign_city=0||is_all_bolt_city=0||is_allow_foreign_back=0||is_aplus_order=0||is_assign=1||is_cross_city_carpool_order=0||is_cross_city_order=0||is_cross_county_order=1||is_destination_hide=0||is_fastcar=0||is_foreign_plate_no_limit=0||is_goodOrder=0||is_holiday=0||is_mixed_payment=0||is_region=1||is_special_price=0||is_stopover_points_order=0||is_workday=1||last_cancel_order_info={"flag":0,"basic_info":{"order_id":577305222745918206,"low_order_id":35238474386174,"passenger_id":"5677960","cur_passenger_id":"5677960","passenger_phone":"15510831780","cur_passenger_phone":"15510831780","require_level":1100,"product_id":11,"extra_type":115268,"starting_lat":40.06994,"starting_lng":116.30629,"cancel_type":1,"order_status":7,"finish_time":1610334443,"current_time":1610334466,"is_cancel_order":1,"is_in_valid_time":1,"duty":0,"is_passenger_duty":0,"is_same_product_id":0,"is_same_require_level":0,"is_in_area":1,"distance":0,"is_same_carpool_type":1,"is_same_passenger_phone":1,"is_both_call_anycar_exception":0}}||lat=40.06994||level_type=0||like_wait=0||limit_cars=-1||lng=116.30629||log_id=1609125366174450094||long_rent_type=0||max_order_num=3||max_seat_num=3||max_walk_radius=0||member_coupon_privileges=[]||member_level_icon=https://dpubstatic.udache.com/static/dpubimg/c214f9b0-2a03-4114-8c39-7630557f2c86.png||member_level_id=4||member_level_name=白金||member_priv_level={}||member_privilege_car_upgrade={}||member_privilege_fast_way={}||member_privilege_priority_answer={}||member_privilege_safe_way={}||mixed_payment_info=||nick=尾号1780||only_night_reservation=0||open_feature=||orderCompleteCount=1351||orderType=0||order_cross_county_forbid=0||order_cross_county_type=1||order_cross_forbid=0||order_cross_province_type=0||order_cross_region_forbid=0||order_cross_type=0||order_end_in_forbid_fence=0||order_product_temp=6||order_source=1||order_start_in_forbid_fence=0||order_station=0||ori_passenger_distribution_group_effect_city=||ori_passenger_distribution_identity=0||ori_passenger_id=5677960||ori_passenger_insurance_distribution_group_id_list=||ori_passenger_organization_distribution_group_id_list=||ori_passenger_white_group_ids=||ori_product_id=11||paid_member_level_id=0||pangu_reward_type=0||partner_id=0||pas_complainted_drunk_num=0||pas_high_risk_female=0||pass_type=0||passagerSignDuringTime=219025373||passagerSignOnTime=1391309093||passenger_age_level=5||passenger_count=0||passenger_distribution_group_effect_city=||passenger_distribution_identity=0||passenger_finish_order_90_flag=0||passenger_gender=-1||passenger_gender_new=-1||passenger_id=5677960||passenger_insurance_distribution_group_id_list=||passenger_organization_distribution_group_id_list=||passenger_phone=15510831780||passenger_register_time=2014-02-02 10:44:53||passenger_resident_city_id1=1||passenger_resident_city_id2=-1||passenger_sex_complaint_count=0||passenger_tags={"high_quality_low_loyalty":false,"high_quality_high_loyalty":false}||passenger_value_type=2.297850728||passenger_version=6.1.2||passenger_vulnerable_tag_count=0||passenger_white_group_ids=||pay_type=0||pay_type_selected=2||poi_dangerous_level=0||poi_end_category=161200||poi_start_category=211000||pre_total_fee=179.98||priority_driver_id=0||product_fields={"blind_type":0,"disability_type":0}||product_id=11||province_id=110000||real_pid=0||refer_driver=0||require_level=1100||require_level_txt=出租车||ride_region=0,223850||robbery_passenger_safety_level=0||route_type=0||rule_female_passenger=4||rule_female_passenger_v3=40||safety_info={"is_need_safety_info":0}||scan_code_type=0||scene_info={"guide_from_airport":0}||scene_type=0||scene_type_copy=0||service_common_group_id_list=||service_common_group_id_list_ori_passenger=||service_supply_group_id_list=||service_supply_group_id_list_ori_passenger=||service_supply_type=0||sex_drunkenness_for_driver=0||sex_passenger_safety_level=0||sex_protectp_passenger_safety_level=7||sex_risk_poi_for_driver=0||silencePassengerDuration=0||silence_tag=0||skyeyeVersionId=skyeyeV7R2||start_dest_distance=53772||start_dest_time=64||start_utc_offset=480||starting_lat=40.06994||starting_lng=116.30629||starting_name=龙域环路|融泽嘉园一号院-西北门||starting_tag=0||station_id=||station_service_control=0||status=0||stopover_points=||strive_car_level=0||strive_time=0000-00-00 00:00:00||target_user=1||tip=0||to_area=1||to_county_id=110113||to_province_id=110000||traffic_safety_shenyeyuyuedan_fuxiang_fast=0||traffic_type=0||unione_pickup_by_meter=0||unione_triffic_limit=1||version=3||walk_type=0||weak_female_passenger=2||weak_female_passenger_v3=201||weak_female_passenger_v7=500||web_app=0||wework_label=100||x_activity_type=0||RES=Y||errno=0||errmsg=ok||tag=tag_triffic_limit||oper_type=2||default_set=1||rule_id=17111002||value_id=17111002,||weight=0||fps_tag={"tag_triffic_limit":{"operation_type":2,"default_set":1,"value":[17111002],"rule_id":[17111002]}}||cost=4`

	orderRuleExp = "area > 0 and ( driver_product_temp == 1 or driver_product_temp == 2 or driver_product_temp == 15 ) and ( ( ( isInList(driver_white_group_ids, 16103455450031) ) ) ) and setResult(1, 1, {30080320})"
}

func ParseExprSub(expr string) (bool, []string) {
	patter := regexp.MustCompile(`^\s*(\w+)\s*\((.*)\)`)
	result := patter.FindAllStringSubmatch(expr, -1)
	fmt.Println(result)
	return true, nil
	// fmt.Println("result1 = ", result1)
}

//ParseOrderOrDriverInfo 解析订单或司机日志
func ParseLogInfo(orderOrDriverLog string) map[string]string {

	infos := strings.Split(orderOrDriverLog, "||")
	var logInfoMap = make(map[string]string, len(infos)-1)
	for _, logInfo := range infos[1:] {
		logInfoKV := strings.Split(logInfo, "=")
		logInfoMap[logInfoKV[0]] = logInfoKV[1]
	}
	return logInfoMap
}

type ExprTreeNode struct {
	name        string
	result      bool
	expr        string
	operator    string
	isLeaf      bool
	isFuncation bool
	children    []*ExprTreeNode
}

func preaseExp() {

}
func PostOrder(head *ExprTreeNode) bool {
	if head == nil {
		return false
	}
	if head.isLeaf == true {
		return head.result
	}
	result := true
	for i, k := range head.children {
		if i == 0 {
			result = PostOrder(k)
		} else {
			if head.operator == "and" {
				result = (result && PostOrder(k))
			} else if head.operator == "or" {
				result = (result && PostOrder(k))
			}
		}
	}
	head.result = result
	fmt.Println(head)
	return result
}
func ParserExpInfo(expr string, head *ExprTreeNode, preIndex int) int {
	expr = strings.Replace(expr, " and ", " & ", -1)
	expr = strings.Replace(expr, " or ", " | ", -1)

	head.isLeaf = false
	operator := "-"
	currentIndex := preIndex
	currentIndex = currentIndex + 1
	var preChar byte = ' '
	for ; currentIndex < len(expr); currentIndex++ {
		c := expr[currentIndex]
		if preIndex < 0 {
			preChar = ' '
		} else {
			preChar = expr[preIndex]
		}
		if c == '(' {
			if currentIndex != 0 && expr[currentIndex-1] == ' ' {
				newTreeNode := &ExprTreeNode{}
				currentIndex = ParserExpInfo(expr, newTreeNode, currentIndex)
				if preChar != ')' {
					head.children = append(head.children, newTreeNode)
				}
				preIndex = currentIndex
			}
		} else if c == '&' {
			exprSub := expr[preIndex+1 : currentIndex-1]
			newTreeNode := &ExprTreeNode{}
			newTreeNode.expr = exprSub
			newTreeNode.isLeaf = true
			operator = "and"
			if preChar != ')' {
				head.children = append(head.children, newTreeNode)
			}
			preIndex = currentIndex
		} else if c == '|' {
			exprSub := expr[preIndex+1 : currentIndex-1]
			newTreeNode := &ExprTreeNode{}
			newTreeNode.expr = exprSub
			newTreeNode.isLeaf = true
			operator = "or"
			if preChar != ')' {
				head.children = append(head.children, newTreeNode)
			}
			preIndex = currentIndex
		} else if c == ')' {
			if expr[currentIndex-1] == ' ' {
				exprSub := expr[preIndex+1 : currentIndex-1]
				newTreeNode := &ExprTreeNode{}
				newTreeNode.expr = exprSub
				newTreeNode.isLeaf = true
				if preChar != ')' {
					head.children = append(head.children, newTreeNode)
				}
				preIndex = currentIndex
				break
			}

		}
	}
	head.operator = operator
	head.name = operator
	return currentIndex

}

func main() {
	ParseExprSub("is(1,2)")
	// setInfo()
	// // _ := ParseLogInfo(orderLogInfo)
	// head := &ExprTreeNode{}
	// ParserExpInfo(orderRuleExp, head, -1)
	// fmt.Println(head)
	// PostOrder(head)
	// fmt.Println(aa)
}
