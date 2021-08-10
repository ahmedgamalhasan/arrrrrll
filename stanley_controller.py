import math


def stanley( input_param, way_points_point, parameter):
    if input_param[0] == 0:
        input_param[0] = 0.0000000000001
    a = -(way_points_point[3]-way_points_point[2])
    b = (way_points_point[1]-way_points_point[0])
    c = (-a)*way_points_point[0]-(b*way_points_point[2])
    yaw = math.atan(-a / b)
    heading_error = yaw-input_param[2]
    if heading_error > math.pi:
        heading_error -= 2*math.pi
    if heading_error < -math.pi:
        heading_error += 2 * math.pi
    crosstrack_error = ((a*input_param[0]+b*input_param[1]+c)/(math.sqrt((a*2)+(b*2))))
    yaw_cross_track = math.atan((input_param[1]-way_points_point[2])/(input_param[0]-way_points_point[0]))
    yaw2ct = yaw - yaw_cross_track
    if yaw2ct > math.pi:
        yaw2ct -= 2 * math.pi
    if yaw2ct < - math.pi:
        yaw2ct += 2 * math.pi
    if yaw2ct > 0:
        crosstrack_error = abs(crosstrack_error)
    else:
        crosstrack_error = - abs(crosstrack_error)
    cross_track_steering = math.atan((parameter[0]*crosstrack_error)/(parameter[3]+input_param[3]))
    steer_angle = heading_error + cross_track_steering
    if steer_angle > parameter[1]:
        steer_angle = parameter[1]
    elif steer_angle < parameter[2]:
        steer_angle = parameter[2]
    print(steer_angle)
    return steer_angle


input_param = [0, 0, 0.349066, 2]      # x  y theta v
way_points = [0, 10, 10, 11]              # x1 x2 y1 y2
param = [0.5, 1.57, -1.57, 1]           # gain   max_steer min_steer sof_param
stanley(input_param, way_points, param)